int IMAGE::Detect_Mark()
{
	delete mark_xvalue;
	delete mark_yvalue;
	delete mark_zvalue;
	mark_number=0;

	int *mark_time=new int[xsize*ysize];
	int *visited=new int[xsize*ysize];
	data_2_value=new unsigned char[xsize*ysize];
	unsigned char *data_temp=0;
	int *data_mark=0;
	unsigned char *data_grey_value=0;
	int total=xsize*ysize;
	int neighber;
	int threshold2=20;
	int mark_length=40;
	int region_number;
//	int *stack_x;
//	int *stack_y;
	int stack_x[10000];
	int stack_y[10000];
	int *area_length;
	int *xtotal;
	int *ytotal;
	int *total_number;
	int block=400;


	total_mark=new int[xsize*ysize];
	for (int i=0;i<xsize*ysize;i++){
		mark_time[i]=-1;
		total_mark[i]=0;
		visited[i]=0;
		data_2_value[i]=0xcd;
	}

	for (int stack=0;stack<stack_size;stack++){
		//for every stack,we first 2 valued them.
		data_temp=data_2_value+xsize;
		data_grey_value=data_2D_stack+stack*total+xsize;
		for (int ypos=1;ypos<ysize-1;ypos++){
			data_temp++;
			data_grey_value++;
			for (int xpos=1;xpos<xsize-1;xpos++){
				neighber=0;
				neighber=*(data_grey_value+1)+*(data_grey_value-1)+*(data_grey_value+xsize)+*(data_grey_value-xsize);
				neighber-=(4*(*data_grey_value));
				neighber=abs(neighber)/4;
				if (neighber>threshold2)
					*data_temp=0;
//				else
//					*data_temp=0xcd;
/*				
				if (*data_grey_value<threshold)
					*data_temp=0;
				else
					*data_temp=0xcd;
*/				data_temp++;
				data_grey_value++;
			}
			data_temp++;
			data_grey_value++;
		}

		//here we set the outer as 0xcd


//		Erosion(&data_2_value,xsize,ysize);
//		Dilation(&data_2_value,xsize,ysize);
		
		data_temp=data_2_value+xsize;
		data_mark=mark_time+xsize;
		region_number=0;

//		stack_x=(int*)malloc(block*sizeof(int));
//		stack_y=(int*)malloc(block*sizeof(int));
		
		int pos=0;
		int *if_visited;
		if_visited=visited+xsize;
		for (ypos=1;ypos<ysize-1;ypos++){
			data_temp++;
			data_mark++;
			if_visited++;
			for (int xpos=1;xpos<xsize-1;xpos++){
				//here we detect and check the right and down four neiighber
				if (*data_temp==0){	//it is a valid edge	
					
					//here we use seed algorithms to grow the area, use 8 neighber
					if (*if_visited==0){				

						stack_x[pos]=xpos;
						stack_y[pos]=ypos;
						pos++;
						while (pos>0){
							int xplace,yplace;
							pos--;
							xplace=stack_x[pos];
							yplace=stack_y[pos];

							int place=yplace*xsize+xplace;

							if ( (*(data_2_value+place-xsize+1)==0) && (*(visited+place-xsize+1)==0) ){
/*								if (pos==block){
									int size=_msize(stack_x);
									stack_x=(int*)realloc(stack_x,size+block*sizeof(int));
									stack_y=(int*)realloc(stack_y,size+block*sizeof(int));
								}
*/								stack_x[pos]=xplace+1;
								stack_y[pos]=yplace-1;
								visited[place-xsize+1]=1;
								pos++;
							}

							if ( (*(data_2_value+place-xsize-1)==0) && (*(visited+place-xsize-1)==0) ){
/*								if (pos==block){
									int size=_msize(stack_x);
									stack_x=(int*)realloc(stack_x,size+block*sizeof(int));
									stack_y=(int*)realloc(stack_y,size+block*sizeof(int));
								}
*/								stack_x[pos]=xplace-1;
								stack_y[pos]=yplace-1;
								visited[place-xsize-1]=1;
								pos++;
							}

							if ( (*(data_2_value+place-xsize)==0) && (*(visited+place-xsize)==0) ){
/*								if (pos==block){
									int size=_msize(stack_x);
									stack_x=(int*)realloc(stack_x,size+block*sizeof(int));
									stack_y=(int*)realloc(stack_y,size+block*sizeof(int));
								}
*/								stack_x[pos]=xplace;
								stack_y[pos]=yplace-1;
								visited[place-xsize]=1;
								pos++;
							}

							if ( (*(data_2_value+place-1)==0) && (*(visited+place-1)==0) ){
/*								if (pos==block){
									int size=_msize(stack_x);
									stack_x=(int*)realloc(stack_x,size+block*sizeof(int));
									stack_y=(int*)realloc(stack_y,size+block*sizeof(int));
								}
*/								stack_x[pos]=xplace-1;
								stack_y[pos]=yplace;
								visited[place-1]=1;
								pos++;
							}

							if ( (*(data_2_value+place+1)==0) && (*(visited+place+1)==0) ){
/*								if (pos==block){
									int size=_msize(stack_x);
									stack_x=(int*)realloc(stack_x,size+block*sizeof(int));
									stack_y=(int*)realloc(stack_y,size+block*sizeof(int));
								}
*/								stack_x[pos]=xplace+1;
								stack_y[pos]=yplace;
								visited[place+1]=1;
								pos++;
							}

							if ( (*(data_2_value+place+xsize+1)==0) && (*(visited+place+xsize+1)==0) ){
/*								if (pos==block){
									int size=_msize(stack_x);
									stack_x=(int*)realloc(stack_x,size+block*sizeof(int));
									stack_y=(int*)realloc(stack_y,size+block*sizeof(int));
								}
*/								stack_x[pos]=xplace+1;
								stack_y[pos]=yplace+1;
								visited[place+xsize+1]=1;
								pos++;
							}

							if ( (*(data_2_value+place+xsize-1)==0) && (*(visited+place+xsize-1)==0) ){
/*								if (pos==block){
									int size=_msize(stack_x);
									stack_x=(int*)realloc(stack_x,size+block*sizeof(int));
									stack_y=(int*)realloc(stack_y,size+block*sizeof(int));
								}
*/								stack_x[pos]=xplace-1;
								stack_y[pos]=yplace+1;
								visited[place+xsize-1]=1;
								pos++;
							}

							if ( (*(data_2_value+place+xsize)==0) && (*(visited+place+xsize)==0) ){
/*								if (pos==block){
									int size=_msize(stack_x);
									stack_x=(int*)realloc(stack_x,size+block*sizeof(int));
									stack_y=(int*)realloc(stack_y,size+block*sizeof(int));
								}
*/								stack_x[pos]=xplace;
								stack_y[pos]=yplace+1;
								visited[place+xsize]=1;
								pos++;
							}
							
							visited[place]=1;
							mark_time[place]=region_number;

						}//end while

						region_number++;

					}//end if ifvisited
				}
				data_temp++;
				data_mark++;
				if_visited++;
			}
			data_temp++;
			data_mark++;
			if_visited++;
		}
		
//		free(stack_x);
//		free(stack_y);
		
		area_length=new int[region_number];
		for (int region=0;region<region_number;region++)
			area_length[region]=0;
		data_mark=mark_time+xsize;
		for (ypos=1;ypos<ysize-1;ypos++){
			data_mark++;
			for (int xpos=1;xpos<xsize-1;xpos++){
				if (*data_mark!=-1)
					area_length[*data_mark]++;
				data_mark++;
			}
			data_mark++;
		}
		
		for (int mark=0;mark<region_number;mark++){
			if (area_length[mark]>mark_length)
				area_length[mark]=0;
		}

		//for each mark,we calculate the x and y value;


		xtotal=new int[region_number];
		ytotal=new int[region_number];
		total_number=new int[region_number];
		for (mark=0;mark<region_number;mark++){
			xtotal[mark]=0;
			ytotal[mark]=0;
			total_number[mark]=0;
		}
		data_mark=mark_time+xsize;
		for (ypos=1;ypos<ysize-1;ypos++){
			data_mark++;
			for (int xpos=1;xpos<xsize-1;xpos++){
				if ((*data_mark!=-1)&&(area_length[*data_mark]!=0)){
					if (*data_mark<region_number){
						xtotal[*data_mark]+=xpos;
						ytotal[*data_mark]+=ypos;
						total_number[*data_mark]++;
					}
				}
				data_mark++;
			}
			data_mark++;
		}

		for (mark=0;mark<region_number;mark++){
			if (total_number[mark]!=0){
				xtotal[mark]/=total_number[mark];
				ytotal[mark]/=total_number[mark];
				total_mark[ytotal[mark]*xsize+xtotal[mark]]++;			
			}
		}

		delete xtotal;
		xtotal=0;
		delete ytotal;
		ytotal=0;
		delete total_number;
		total_number=0;
		delete area_length;
		area_length=0;


/*
		for (mark=0;mark<xsize*ysize;mark++){
			if (total_mark[mark]==0)
				total_mark[mark]=0xff;
			else
				total_mark[mark]=1;
			if (data_2_value[mark]==0xcd)
				data_2_value[mark]=0xff;
			else
				data_2_value[mark]=1;
		}
*/
//		break;
	}

	for (int place=0;place<xsize*ysize;place++)
		if (total_mark[place]<stack_size/2)
			total_mark[place]=0xff;
		else
			total_mark[place]=1;


//	delete data_2_value;
//	delete xtotal;
//	delete ytotal;
//	delete total_number;
	delete mark_time;
//	delete total_mark;

	return 0;
}