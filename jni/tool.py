import os,glob

file_list = glob.glob('res/*');
print(file_list)
for each in file_list:
    low = each.lower();
    print(low)
    os.rename(each, low);


