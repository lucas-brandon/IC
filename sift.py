import numpy as np
import cv2 as cv
import sys

#print('poha,aqui',sys.argv)

nomeImagem=sys.argv[1]

variaveis = nomeImagem.split(",");
print(variaveis)

variaveis[1] = int(variaveis[1]) - 320
variaveis[2] = 240-int(variaveis[2])
variaveis[3] = int(variaveis[3]) - 320
variaveis[4] = 240-int(variaveis[4])

print("aquii teste",variaveis[0])
img = cv.imread(variaveis[0])
#gray= cv.cvtColor(img,cv.COLOR_BGR2GRAY)
sift = cv.xfeatures2d.SIFT_create()
kp = sift.detect(img,None)

index = []
for point in kp:
    index.append(point.pt)

i=0
j = len(index)-1

while(i<=j):

    if(((index[i][0]-320) < variaveis[1]+20) or ((index[i][0]-320) >  variaveis[3]-20)or ((240-index[i][1]) > variaveis[2]-200) or ((240-index[i][1]) < variaveis[4])):
        kp.pop(i)
        index.pop(i)
        i=i-1
        j=j-1

    i=i+1



#while(len(kp) !=3 ):
#    kp.pop(0)


#print(kp)
img=cv.drawKeypoints(img,kp,img)


#print("X: ",index[0][0]-320," Y: ",240-index[0][1])
#print("X: ",index[1][0]-320," Y: ",240-index[1][1])
#print("X: ",index[2][0]-320," Y: ",-320index[2][1])

cv.imwrite('sift_'+variaveis[0],img)


img2 = cv.imread('sift_'+variaveis[0],cv.IMREAD_COLOR)
cv.imshow('image',img2)
cv.waitKey(0)
cv.destroyAllWindows()

f = open('file_'+variaveis[0]+'.txt',"w+")


for i in range(len(index)):
 f.write("%f %f\n" % (index[i][0]-320,240-index[i][1]))


f.close()
