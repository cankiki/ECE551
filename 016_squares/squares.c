int max(int x,int y){
  if(x>y){
  return x;
  }
  else{
  return y;
  }
}
int is_between(int x,int y,int z){
if(x>=y&&x<z){
return 1;
}
else{
return 0;
}
}

int is_equal(int x,int y,int z){
if(x==y||x==z){
return 1;
}
else{
return 0;
}
}

int is_less(int x,int y){
if(x<y){
return 1;
}
else{
return 0;
}
}

int is_either(int x,int y){
if(x==0||x==y){
return 1;
}
else{
return 0;
}
}




void squares(int size1, int x_offset, int y_offset, int size2) {
  
  int w=max(size1,x_offset + size2);//compute the max of size1 and (x_offset + size2).  Call this w

  int h=max(size1,y_offset + size2);//compute the max of size1 and (y_offset + size2).  Call this h

   for (int y=0; y<h; y++){//count from 0 to h. Call the number you count with y

    for (int x=0; x<w; x++){//count from 0 to w. Call the number you count with x
    int a=is_between(x,x_offset,x_offset+size2);
    int b=is_between(y,y_offset,y_offset+size2);
    int c=is_equal(x,x_offset,x_offset+size2-1);
    int d=is_equal(y,y_offset,y_offset+size2-1);
    int e=a&&d;  
    int f=b&&c;
    int g=is_less(x,size1);
    int z=is_less(y,size1);
    int k=is_either(x,size1-1);
    int l=is_either(y,size1-1);
    int m=g&&l;
    int n=z&&k;
      if(e||f){
      printf("*");
      }//check if  EITHER
      //    ((x is between x_offset  and x_offset +size2) AND 
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
      //  OR
      //    ((y is between y_offset and y_offset + size2) AND
      //     x is equal to either x_offset OR x_offset + size2 -1)
      // if so, print a *
        else if(m||n){
      printf("#");
      }
      //if not,
      // check if EITHER
      //    x is less than size1 AND (y is either 0 or size1-1)
      // OR
      //    y is less than size1 AND (x is either 0 or size1-1)
      //if so, print a #
    else{
    printf(" ");//else print a space
    }
    }
    printf("\n"); 
    }  
    //when you finish counting x from 0 to w, 
    //print a newline

}

