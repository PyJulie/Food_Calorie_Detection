import os
path = 'D:\\caomei\\'
newpath = 'D:\\newcaomei\\'
for file in os.listdir(path):
    if os.path.isfile(os.path.join(path,file))==True:
            newname='2_'+file
            os.rename(os.path.join(path,file),os.path.join(newpath,newname))
