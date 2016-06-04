# coding=utf-8
import cv2
import numpy as np
import pickle
from matplotlib import pyplot as plt
#标本名字（文件放在同一目录中）
name=['leaf1.jpg','leaf2.jpg','leaf3.jpg','leaf4.jpg','leaf5.jpg']

for item in name:
    #图片预处理
    img1 = cv2.imread("res/"+item,0)
    img2  = cv2.medianBlur(img1,5)
    img = cv2.GaussianBlur(img2,(5,5),0)
    #Otsu’s 二值化
    ret,thresh = cv2.threshold(img,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)
    #找轮廓（可能有很多个轮廓）
    contours,hierarchy = cv2.findContours(thresh, 1,cv2.CHAIN_APPROX_NONE)

    per=[]
    #计算轮廓周长
    for cnt in contours:
           perimeter = cv2.arcLength(cnt,True)
           per.append( perimeter )
    #对周长排序
    sorted(per)
    #寻找第二长周长的轮廓，这个轮廓就是要找的轮廓
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
    #将性质参数存在一个列表中
    data=[item,aspect_ratio ,extent,solidity,equi_diameter]
    #write pickle file（写文件以备比对使用）
    try:
           with open('data/'+item+".txt","w") as file_data:
                   pickle.dump(data,file_data)
    except IOError as err:
           print('File error'+str(err))


    print "/n"
    print "长宽比为",aspect_ratio
    print "轮廓面积与边界甘矩形面积的比",extent
    print "轮廓面积与凸包元面积的比",solidity
    print "与轮廓面积相等的柱圆形的直径",equi_diameter
