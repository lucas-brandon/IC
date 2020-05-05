import cv2
import numpy as np
from matplotlib import pyplot as plt
import sys
import pyautogui
import matplotlib.patches as patches
from PIL import Image
import numpy as np

nomeImagem=sys.argv[1]
nomeTextoPontoFronteira=sys.argv[2]
rangeOfRead = sys.argv[3]
#f=open(nomeTextoPontoFronteira, "r")
#contents =f.readlines()
dpi = plt.rcParams['figure.dpi']
im_data = plt.imread(nomeImagem,0)
height, width, depth = im_data.shape
contador=0
# What size does the figure need to be in inches to fit the image?
figsize = width / float(dpi), height / float(dpi)
vetorPontosArquivos=[]#vetor para o tamanho dos pontos
distanciasPdm=[]

# Create a figure of the right size with one axes that takes up the full figure
fig = plt.figure(figsize=figsize)
ax = fig.add_axes([0, 0, 1, 1])
vetorPontos=[]
ponto=[]
pontosDoCanny=[]
ax.axis('off')
edges = cv2.Canny(im_data,50,100)
ax.imshow(edges, cmap='gray')

for ix in range(0,int(rangeOfRead),1):
    f=open(nomeTextoPontoFronteira+str(ix), "r")
    contents = f.readlines()
    pts=[]#pontos dos arquivos
    #print("Arquivo: ",ix)
    for ct in contents:
        txt = ct.split(",")
        #print(ct[0],ct[1],ct[2])
        print(txt)
        pts.append(float(txt[0]))
        pts.append(float(txt[1]))

    vetorPontosArquivos.append(pts)


def display_pdm_distance():
    #print('começo aqui: ',vetorPontosArquivos)
    #calculando PDM de F1 para F2 (dos pontos de fronteira para os pontos do canny)
    for i in range(0,len(vetorPontosArquivos),1):#esses são os pontos de fronteira
        for j in range(1,len(vetorPontosArquivos[i]),2):
            x1=vetorPontosArquivos[i][j-1]
            y1=vetorPontosArquivos[i][j]
            for k in range(1,len(pontosDoCanny),1):#canny deve retornar pelo menos 2 pontos para comparar, senão o programa crasha "er er"
                    x2=pontosDoCanny[k-1]
                    y2=pontosDoCanny[k]
                    ly=

def onclick(event):

    global contador
    if contador <= 1:
        plt.scatter(int(event.xdata), int(event.ydata), s=15)
        fig.canvas.draw()
        contador=contador+1
        ponto.append(int(event.xdata))
        ponto.append(int(event.ydata))
        print(ponto)
        vetorPontos.append(ponto)

    if contador==2:

        contador=contador+1
        print(vetorPontos)
        rect = patches.Rectangle((vetorPontos[0][0],vetorPontos[0][1]),vetorPontos[1][2]-vetorPontos[0][0],vetorPontos[1][3]-vetorPontos[0][1],linewidth=1,edgecolor='r',facecolor='none')
        ax.add_patch(rect)

        if vetorPontos[0][0] < vetorPontos[0][2] and vetorPontos[0][1] < vetorPontos[0][3]:

            for i in range(vetorPontos[0][0],vetorPontos[0][2],1):
                for j in range(vetorPontos[0][1],vetorPontos[0][3],1):
                     if(edges[j,i] >= 250):
                         plt.scatter(i,j, s=2,color="red")
                         pontosDoCanny.append(i-320)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)
                         pontosDoCanny.append(240-j)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)


        elif vetorPontos[0][0] > vetorPontos[0][2] and vetorPontos[0][1] > vetorPontos[0][3]:
            for i in range(vetorPontos[0][0],vetorPontos[0][2],-1):
                for j in range(vetorPontos[0][1],vetorPontos[0][3],-1):
                     if(edges[j,i] >= 250):
                         plt.scatter(i,j, s=2,color="red")
                         pontosDoCanny.append(i-320)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)
                         pontosDoCanny.append(240-j)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)

        elif vetorPontos[0][0] > vetorPontos[0][2] and vetorPontos[0][1] < vetorPontos[0][3]:
            for i in range(vetorPontos[0][0],vetorPontos[0][2],-1):
                for j in range(vetorPontos[0][1],vetorPontos[0][3],1):
                     if(edges[j,i] >= 250):
                         plt.scatter(i,j, s=2,color="red")
                         pontosDoCanny.append(i-320)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)
                         pontosDoCanny.append(240-j)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)

        elif vetorPontos[0][0] < vetorPontos[0][2] and vetorPontos[0][1] > vetorPontos[0][3]:
            for i in range(vetorPontos[0][0],vetorPontos[0][2],1):
                for j in range(vetorPontos[0][1],vetorPontos[0][3],-1):
                     if(edges[j,i] >= 250):
                         plt.scatter(i,j, s=2,color="red")
                         pontosDoCanny.append(i-320)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)
                         pontosDoCanny.append(240-j)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)

        fig.canvas.draw()
        print('pontos do canny ',pontosDoCanny)
        display_pdm_distance()



def display_image_in_actual_size():
    cid = fig.canvas.mpl_connect('button_press_event', onclick)
    plt.show()


display_image_in_actual_size()
