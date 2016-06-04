# coding=utf-8
import cv2
import numpy as np
import pickle
from matplotlib import pyplot as plt
#标本列表
name=['leaf1.jpg','leaf2.jpg','leaf3.jpg','leaf4.jpg','leaf5.jpg']
#识别对象
test=['test.jpg']
new=[]
std_list=[]
#图片预处理
img1 = cv2.imread("res/test.jpg",0)
img2  = cv2.medianBlur(img1,5)
img = cv2.GaussianBlur(img2,(5,5),0)
#Otsu’s 二值化
ret,thresh = cv2.threshold(img,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)
#寻找轮廓（可能多个）
contours,hierarchy = cv2.findContours(thresh, 1,cv2.CHAIN_APPROX_NONE)
#寻找第二长周长，也就是目标轮廓
per=[]
for cnt in contours:
       perimeter = cv2.arcLength(cnt,True)
       per.append( perimeter )
sorted(per)
for select in contours:
        if per[-2]== cv2.arcLength(select,True):
              break
#绘出轮廓
cv2.drawContours(img,select,-1,(0,0,200),3)

#性质列表
#长宽比
x,y,w,h = cv2.boundingRect(select)
aspect_ratio = float(w)/h
#边界面积
area = cv2.contourArea(select)
rect_area=w*h
extent = float(area)/rect_area
#轮廓面积与凸包面积的比
hull = cv2.convexHull(select)
hull_area = cv2.contourArea(hull)
solidity = float(area)/hull_area #  if hull_area !=0:
#与轮廓面积相等的圆形的直径
equi_diameter = np.sqrt(4*area/np.pi)

cv2.imshow("select",img)
cv2.waitKey(0)
#识别对象目标的性质参数
object_data=["test.jpg",aspect_ratio ,extent,solidity,equi_diameter]

#读取标本的性质参数
for item in name:
    try:
        with open("data/"+item+".txt",'r') as file:
            new=pickle.load(file)
    except IOError as err:
        print('File error:'+str(err) )
    except pickle.PickleError as perr:
        print('Pickling error: '+str(perr))
    result=[]
    #计算前三个性质的标准差
    att1=object_data[1]-new[1]
    result.append(att1)
    att2=object_data[2]-new[2]
    result.append(att2)
    att3=object_data[3]-new[3]
    result.append(att3)
    #标准差
    std=np.std(result,axis=0)
    std_list.append(std)
#标准差从小到大进行排序
sorted_std_list=sorted(std_list)
#print(sorted_std_list)

#寻找标准差最小的标本
for item in name:
    try:
        with open("data/"+item+".txt",'r') as file:
            new=pickle.load(file)
    except IOError as err:
        print('File error:'+str(err) )
    except pickle.PickleError as perr:
        print('Pickling error: '+str(perr))
    result=[]
    att1=object_data[1]-new[1]
    result.append(att1)
    att2=object_data[2]-new[2]
    result.append(att2)
    att3=object_data[3]-new[3]
    result.append(att3)
    #标准差
    std=np.std(result,axis=0)
    if sorted_std_list[0]== std:
        break
#得到结果
print("匹配的树叶是"+item)
