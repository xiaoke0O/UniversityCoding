clc,clear
%读图像
img=imread('TM3.bmp');
figure;
subplot(2,3,1),imshow(img),title("Original image");

%二值化处理
if ndims(img)~=3
    img_gray=img;
else
img_gray=rgb2gray(img);
end
img_bw=imbinarize(img_gray);
subplot(2,3,2),imshow(img_bw),title("Binary image");

%初步筛选
[x,y]=size(img_bw);
PrimaryResult=zeros(x,y,'uint8');
for i=2:x-1
    for j=2:y-1
        dg1=abs(img_bw(i,j)-img_bw(i+1,j));
        dg2=abs(img_bw(i,j)-img_bw(i,j+1));
        dg3=abs(img_bw(i,j)-img_bw(i-1,j));
        dg4=abs(img_bw(i,j)-img_bw(i,j-1));
        dg=sort([dg1,dg2,dg3,dg4]);
        if dg(3)==1
            PrimaryResult(i,j)=255;
        end
    end
end
subplot(2,3,3),imshow(PrimaryResult),title(" Primary results");

%进一步筛选，计算协方差矩阵与误差椭圆
FurtherResult=PrimaryResult;
WeightMatrix=zeros(x,y)
Tq=0.8;%??
for i=2:x-1
    for j=2:y-1
        if PrimaryResult(i,j)==255
            gu2=0;
            gv2=0;
            guv=0;
            for ii=i-1:i
                for jj=j-1:j
                 gu2=gu2+(img_bw(ii+1,jj+1)-img_bw(ii,jj))^2; 
                 gv2=gv2+(img_bw(ii,jj+1)-img_bw(ii+1,jj))^2;
                 guv=guv+(img_bw(ii+1,jj+1)-img_bw(ii,jj))*(img_bw(ii,jj+1)-img_bw(ii+1,jj));
                end
            end
            DetN=gu2*gv2-guv^2;
            trN=gu2+gv2;
            q=4*DetN/(trN^2);
            if q>Tq
                WeightMatrix(i,j)=DetN/trN;
            else
                FurtherResult(i,j)=0;
            end
        end
    end
end
subplot(2,3,4),imshow(FurtherResult),title("Further Result");

%最终点位获取
FinalReault=FurtherResult;
vmsize=5;%????
wradius=floor(vmsize/2);
for i=wradius+1:x-wradius
    for j=wradius+1:y-wradius
        if(FurtherResult(i,j)==255)
            tempiv=WeightMatrix(i-wradius:i+wradius,j-wradius:j+wradius);
            tempsort=sort(tempiv(:),'descend');
            if WeightMatrix(i,j)==tempsort(1)&&WeightMatrix(i,j)~=tempsort(2)
                ;
            else
                FinalReault(i,j)=0;
            end
        end
    end
end
% 最终提取的点和原始图像叠加显示
subplot(2,3,5),imshow(FinalReault),title('Finall Result');
subplot(2,3,6),imshow(img),title("Original image"),hold,spy(FinalReault,'-r.');