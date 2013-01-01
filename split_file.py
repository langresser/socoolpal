import sys
from os.path import exists
fileCount = 0

def splitFile(fileName, partSize=1000):
    # 1024 * 1024 = 1048576
    length = partSize * 1024
    print(length);
    global fileCount
    fileCount = 0;
    f1 = open(fileName, "rb")
    while True:
        content = f1.read(length)
        if content == "" or content == None or len(content) == 0:
            break
        newFile = distFile(fileName)
        f2 = open(newFile, "wb")
        f2.write(content)
        f2.close()

        if fileCount >= 40:
            break;
    f1.close()
    print('split file complete!')
   

def distFile(sourceFile):
    global fileCount
    fileCount = fileCount + 1
    extPos = sourceFile.rfind('.')
    if extPos > 0:
        return sourceFile + '.part' + str(fileCount)
    else:    # extPos == -1
        print('File type? Can not split!')
        sys.exit(1)

def combine(filename):
    count = 0
    extPos = filename.find('.part')
    if extPos > 0:
        file = filename[:extPos]
        f1 = open(file, "wb")
        while True:
            count = count + 1
            partFile = file + '.part' + str(count)
            if not exists(partFile):
                break
            else:
                f2 = open(partFile, "rb")
                content = f2.read()
                f2.close()
                f1.write(content)
        f1.close()
        print('combine file complete!')

    else:
        print('File type? Can not combine!')



splitFile("splitres/fbp.mkf");
splitFile("splitres/gop.mkf");
splitFile("splitres/map.mkf");
splitFile("splitres/mgo.mkf");
splitFile("splitres/rng.mkf");
splitFile("splitres/voc.mkf");