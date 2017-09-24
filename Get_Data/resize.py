import os
from PIL import Image
import glob
path = 'D:/DATA/caomei/'
i=1
def convertjpg(jpgfile,outdir,width=64,height=64):
    img=Image.open(jpgfile)
    new_img=img.resize((width,height),Image.BILINEAR)
    new_img.save(os.path.join(outdir,os.path.basename(jpgfile)))
for jpgfile in glob.glob("D:/DATA/caomei/*.jpg"):
    convertjpg(jpgfile,"D:/DATA")