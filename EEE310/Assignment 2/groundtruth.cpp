 //定义变量和初始化
 ifstream infile;
 infile.open("C:\\pyhon program\\Mask_RCNN-master\\gt_terrace.txt");   //将文件流对象与文件连接起来 
 assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 
 string input_s;
 getline(infile, input_s);
 getline(infile, input_s);
 getline(infile, input_s);//ground turth文件前两行没有有效信息从第三行开始读
 

//之后是while(1)后添加的内容，即没帧处理内容
 //format of ground truth
 // 1 <number of frames>  <number of people>  <grid width>  <grid height>  <step size>  <first frame>  <last frame> <pos> <pos> <pos> ... <pos> <pos> <pos> ... . . .
 gt_n.clear();
 for (int i_in = 0; i_in < 9; i_in++)
 {
      infile >> input_int;//按顺序读出下一个位置的数值
      //cout << input_int << " ";
      if (input_int >= 0)
      gt_n.push_back(input_int);
 }

 vector<int> gt_n;
 vector<Rect> gt;
 vector<int> result;
 int countHit = 0; //correct detection
 int countdet = 0; // num of detection
 int countGT = 0; //num of pedestrians
 Point LT(290,285), RB(460,450) //AOI的左上角和右下角点

   float overlap;

   bool flagdraw;
   bool flagmiss = 0; //Missing flag

   int miss_count = 0;
   int miss_countk = 0;

   countdet = countdet + result.size();//detected results count

   for (int i = 0; i < result.size(); i++)
   {
    // In the actual calculation, the AOI will be larger. The range of the AOI including the buffer on the top view is LT.x-5, RB.x + 5, LT.y-5, RB.y + 5
    if (!(camera[0]->p[result[i]].x >= LT.x - 5 && camera[0]->p[result[i]].x <= RB.x + 5 && camera[0]->p[result[i]].y >= LT.y - 5 && camera[0]->p[result[i]].y <= RB.y + 5))
     //If it is not within the range of AOI and buffer, the number of detections will be -1
     countdet--;
   }

   int ga, gb, gn; //ga and gb represent the position information of ground truth on the top view, ga represents the x coordinate, gb represents the y coordinate
   if (gt_n.size() > 0)
   {
    gt.clear();
    for (int gt_in = 0; gt_in < gt_n.size(); gt_in++)
    {
     flagdraw = 0;
     ga = gt_n[gt_in] % 30 * 250 + 125 - 500; //将ground truth 的网格坐标点换算成世界坐标
     gb = gt_n[gt_in] / 30 * 250 + 125 - 1500;

     ga = ga / 30 + 250;//将世界坐标点换算为顶视图坐标
     gb = gb / 30 + 250;

     for (int k = 0; k < camera.size(); k++)
     {
      gt.push_back(Rect(camera[k]->rctMap.at<Vec4f>(ga, gb)[0], camera[k]->rctMap.at<Vec4f>(ga, gb)[1], camera[k]->rctMap.at<Vec4f>(ga, gb)[2], camera[k]->rctMap.at<Vec4f>(ga, gb)[3]));
     }

     flag1 = 0;
     for (int k = 0; k < camera.size(); k++)
     {
      if (camera[k]->topshow.at<uchar>(ga, gb) == 1)
       flag1++;
     }

     if (flag1 >= 1)
      if (ga >= LT.x - 5 && ga <= RB.x + 5 && gb >= LT.y - 5 && gb <= RB.y + 5)
      {
       countGT++;

       for (int i = 0; i < result.size(); i++)
       {
        flagdraw = 0;
        for (int k = 0; k < camera.size(); k++)
        {
         if (camera[k]->topshow.at<uchar>(ga, gb) == 1)
         {
          //The points in the ground truth calculate the coincidence rate directly in all views and all candidate boxes
          overlap = bbOverlap(Rect(camera[k]->rctMap.at<Vec4f>(ga, gb)[0], camera[k]->rctMap.at<Vec4f>(ga, gb)[1], camera[k]->rctMap.at<Vec4f>(ga, gb)[2], camera[k]->rctMap.at<Vec4f>(ga, gb)[3]), camera[k]->r[result[i]]);

          //小于0.3的情况
          if (overlap < 0.3)
          {
           //rectangle(camera[k]->frame2, Rect(camera[k]->rctMap.at<Vec4f>(ga, gb)[0], camera[k]->rctMap.at<Vec4f>(ga, gb)[1], camera[k]->rctMap.at<Vec4f>(ga, gb)[2], camera[k]->rctMap.at<Vec4f>(ga, gb)[3]), CV_RGB(255, 255, 255), 2);
           //If the frame aspect ratio at the ga gb point is not correct and is close to the edge of the view, then set flagdet to 1
           if ((camera[k]->rctMap.at<Vec4f>(ga, gb)[0] <= 2
            || (camera[k]->rctMap.at<Vec4f>(ga, gb)[0] + camera[k]->rctMap.at<Vec4f>(ga, gb)[2]) >= camera[k]->frame.cols - 2)
            && camera[k]->rctMap.at<Vec4f>(ga, gb)[2] / camera[k]->rctMap.at<Vec4f>(ga, gb)[3] < 0.34)
            //&& camera[k]->rctMap.at<Vec4f>(ga, gb)[2] / camera[k]->rctMap.at<Vec4f>(ga, gb)[3] <= 0.36)
           {
            //flagdet = 1;
            //continue;
           }
           else
           {
            flagdraw = 1;
            //rectangle(camera[k]->frame2, Rect(camera[k]->rctMap.at<Vec4f>(ga, gb)[0], camera[k]->rctMap.at<Vec4f>(ga, gb)[1], camera[k]->rctMap.at<Vec4f>(ga, gb)[2], camera[k]->rctMap.at<Vec4f>(ga, gb)[3]), CV_RGB(255, 255, 255), 2);
            //countHit++;





            //
            //cout <<"rctMap(ga,gb)[0]"<<""<< camera[k]->rctMap.at<Vec4f>(ga, gb)[0] << endl;
            //cout << "rctMap(ga,gb)[1]" << "" << camera[k]->rctMap.at<Vec4f>(ga, gb)[1] << endl;
            //cout << "rctMap(ga,gb)[2]" << "" << camera[k]->rctMap.at<Vec4f>(ga, gb)[2] << endl;
            //cout << "rctMap(ga,gb)[3]" << "" << camera[k]->rctMap.at<Vec4f>(ga, gb)[3] << endl;
            break;
           }
          }
         }
        }
        if (!flagdraw)
        {
         //When there is a match between the detection box and the ground truth box, for countHit ++, countHit means the correct number of detections
         countHit++;
         for (int k = 0; k < camera.size(); k++)
         {

          if (camera[k]->topshow.at<uchar>(ga, gb) == 1)
          {
           ;// rectangle(camera[k]->frame, Rect(camera[k]->rctMap.at<Vec4f>(ga, gb)[0], camera[k]->rctMap.at<Vec4f>(ga, gb)[1], camera[k]->rctMap.at<Vec4f>(ga, gb)[2], camera[k]->rctMap.at<Vec4f>(ga, gb)[3]), CV_RGB(255, 0, 0), 2);
          }
         }
         break;
        }
       }
       if (flagdraw)
       {
        for (int k = 0; k < camera.size(); k++)
        {
         if (camera[k]->topshow.at<uchar>(ga, gb) == 1)
         {
          //Set up a buffer at the AOI boundary If the ground truth point is in the buffer, this ground truth point is not counted
          if (abs(ga - LT.x) < 5 || abs(gb - LT.y) < 5 || abs(ga - RB.x) < 5 || abs(gb - RB.y) < 5)
          {
           countGT--;
           flagmiss = 1;
           break;
          }
         }
        }

        if (flagmiss == 0)
        {
         for (int k = 0; k < camera.size(); k++)
         {
          if (camera[k]->topshow.at<uchar>(ga, gb) == 1)
          {
           // rectangle(camera[k]->frame, Rect(camera[k]->rctMap.at<Vec4f>(ga, gb)[0], camera[k]->rctMap.at<Vec4f>(ga, gb)[1], camera[k]->rctMap.at<Vec4f>(ga, gb)[2], camera[k]->rctMap.at<Vec4f>(ga, gb)[3]), CV_RGB(0, 255, 0), 2);
          }
         }
        }
        else
         flagmiss = 0;

       }

      }


    }
   }

//The following is the result block
 cout << endl << endl << endl;
 //cout << countGT << " " << countdet << " " << countHit << endl;
 cout << "FN " << countGT - countHit << endl; //FN false negative 即漏检个数
 //cout << "FN rate" << (countGT - countHit) / double(countGT) << endl;
 cout << "FP " << countdet - countHit << endl; //FP false positive 即phantoms数量
 //cout << "FP rate" << (countdet - countHit) / double(countdet) << endl;
 cout << "MDR " << (countGT - countHit) / double(countGT) << endl; //MDR  missed detection rate
 cout << "FDR " << (countdet - countHit) / double(countGT) << endl; // FDR false detection rate
 cout << "TER " << ((countGT - countHit) + (countdet - countHit)) / double(countGT) << endl; //TER total error rate
 cout << "PRE " << countHit / double(countdet) << endl; //PRE precision
 cout << "REC " << countHit / double(countGT) << endl;// REC recall

