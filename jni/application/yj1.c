//
// PAL DOS compress format (YJ_1) library
//
// Author: Lou Yihua <louyihua@21cn.com>
//
// Copyright 2006 - 2007 Lou Yihua
//
// This file is part of PAL library.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
//

// Ported to C from C++ and modified for compatibility with Big-Endian
// by Wei Mingzhi <whistler@openoffice.org>.

#include "common.h"

typedef struct _TreeNode
{
   unsigned char   value;
   unsigned char   leaf;
   unsigned short  level;
   unsigned int    weight;

   struct _TreeNode *parent;
   struct _TreeNode *left;
   struct _TreeNode *right;
} TreeNode;

typedef struct _TreeNodeList
{
   TreeNode *node;
   struct _TreeNodeList *next;
} TreeNodeList;

typedef struct _YJ_1_FILEHEADER
{
   unsigned int	Signature;          // 'YJ_1'
   unsigned int	UncompressedLength; // size before compression
   unsigned int	CompressedLength;   // size after compression
   unsigned short BlockCount;       // number of blocks
   unsigned char Unknown;
   unsigned char HuffmanTreeLength; // length of huffman tree
} YJ_1_FILEHEADER, *PYJ_1_FILEHEADER;

typedef struct _YJ_1_BLOCKHEADER
{
   unsigned short UncompressedLength; // maximum 0x4000
   unsigned short CompressedLength;   // including the header
   unsigned short LZSSRepeatTable[4];
   unsigned char LZSSOffsetCodeLengthTable[4];
   unsigned char LZSSRepeatCodeLengthTable[3];
   unsigned char CodeCountCodeLengthTable[3];
   unsigned char CodeCountTable[2];
} YJ_1_BLOCKHEADER, *PYJ_1_BLOCKHEADER;

static unsigned int
get_bits(
   const void *src,
   unsigned int *bitptr,
   unsigned int count
)
{
   unsigned char *temp = ((unsigned char *)src) + ((*bitptr >> 4) << 1);
   unsigned int bptr = *bitptr & 0xf;
   unsigned short mask;
   *bitptr += count;
   if (count > 16 - bptr)
   {
      count = count + bptr - 16;
      mask = 0xffff >> bptr;
      return (((temp[0] | (temp[1] << 8)) & mask) << count) | ((temp[2] | (temp[3] << 8)) >> (16 - count));
   }
   else
      return (((unsigned short)((temp[0] | (temp[1] << 8)) << bptr)) >> (16 - count));
}

static unsigned short
get_loop(
   const void *src,
   unsigned int *bitptr,
   PYJ_1_BLOCKHEADER header
)
{
   if (get_bits(src, bitptr, 1))
      return header->CodeCountTable[0];
   else
   {
      unsigned int temp = get_bits(src, bitptr, 2);
      if (temp)
         return get_bits(src, bitptr, header->CodeCountCodeLengthTable[temp - 1]);
      else
         return header->CodeCountTable[1];
   }
}

static unsigned short
get_count(
   const void *src,
   unsigned int *bitptr,
   PYJ_1_BLOCKHEADER header
)
{
   unsigned short temp;
   if ((temp = get_bits(src, bitptr, 2)) != 0)
   {
      if (get_bits(src, bitptr, 1))
         return get_bits(src, bitptr, header->LZSSRepeatCodeLengthTable[temp - 1]);
      else
         return SWAP16(header->LZSSRepeatTable[temp]);
   }
   else
      return SWAP16(header->LZSSRepeatTable[0]);
}

INT
DecodeYJ1(
   LPCVOID       Source,
   LPVOID        Destination,
   INT           DestSize
)
{
   PYJ_1_FILEHEADER hdr = (PYJ_1_FILEHEADER)Source;
   unsigned char *src = (unsigned char *)Source;
   unsigned char *dest;
   unsigned int i;
   TreeNode *root, *node;

   if (Source == NULL)
      return -1;
   if (SWAP32(hdr->Signature) != 0x315f4a59)
      return -1;
   if (SWAP32(hdr->UncompressedLength) > (unsigned int)DestSize)
      return -1;

   do
   {
      unsigned short tree_len = ((unsigned short)hdr->HuffmanTreeLength) * 2;
      unsigned int bitptr = 0;
      unsigned char *flag = (unsigned char *)src + 16 + tree_len;

      if ((node = root = (TreeNode *)malloc(sizeof(TreeNode) * (tree_len + 1))) == NULL)
         return -1;
      root[0].leaf = 0;
      root[0].value = 0;
      root[0].left = root + 1;
      root[0].right = root + 2;
      for (i = 1; i <= tree_len; i++)
      {
         root[i].leaf = !get_bits(flag, &bitptr, 1);
         root[i].value = src[15 + i];
         if (root[i].leaf)
            root[i].left = root[i].right = NULL;
         else
         {
            root[i].left =  root + (root[i].value << 1) + 1;
            root[i].right = root[i].left + 1;
         }
      }
      src += 16 + tree_len + (((tree_len & 0xf) ? (tree_len >> 4) + 1 : (tree_len >> 4)) << 1);
   } while (0);

   dest = (unsigned char *)Destination;

   for (i = 0; i < SWAP16(hdr->BlockCount); i++)
   {
      unsigned int bitptr;
      PYJ_1_BLOCKHEADER header;

      header = (PYJ_1_BLOCKHEADER)src;
      src += 4;
      if (!SWAP16(header->CompressedLength))
      {
         unsigned short hul = SWAP16(header->UncompressedLength);
         while (hul--)
         {
            *dest++ = *src++;
         }
         continue;
      }
      src += 20;
      bitptr = 0;
      for (;;)
      {
         unsigned short loop;
         if ((loop = get_loop(src, &bitptr, header)) == 0)
            break;

         while (loop--)
         {
            node = root;
            for(; !node->leaf;)
            {
               if (get_bits(src, &bitptr, 1))
                  node = node->right;
               else
                  node = node->left;
            }
            *dest++ = node->value;
         }

         if ((loop = get_loop(src, &bitptr, header)) == 0)
            break;

         while (loop--)
         {
            unsigned int pos, count;
            count = get_count(src, &bitptr, header);
            pos = get_bits(src, &bitptr, 2);
            pos = get_bits(src, &bitptr, header->LZSSOffsetCodeLengthTable[pos]);
            while (count--)
            {
               *dest = *(dest - pos);
               dest++;
            }
         }
      }
      src = ((unsigned char *)header) + SWAP16(header->CompressedLength);
   }
   free(root);

   return SWAP32(hdr->UncompressedLength);
}
