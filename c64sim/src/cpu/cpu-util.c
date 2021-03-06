/*
  initial: 31.1.2015
  implement inc_pc
  16.8.2015: implement step
*/

//#include "cpu.h"
#include "decode.h"

int inc_pc(struct _6510_cpu* cpu){
  int i= 7;
  while(i>-1){
	if(cpu->pcl[i]=='0'){
	  cpu->pcl[i] = '1';
	  return i;
	}else
	  cpu->pcl[i] = '0';
	i--;
  }
  i = 7;
  while(i>-1){
	if(cpu->pch[i]=='0'){
	  cpu->pch[i] = '1';
	  return i;
	}else
	  cpu->pch[i] = '0';
	i--;
  }
  return i;
  
  //  if(i==-1)
  //	printf("Error: PC reached End Of Memory");
}

int dec_pc(struct _6510_cpu* cpu){
  int i= 7;
  while(i>-1){
	if(cpu->pcl[i]=='1'){
	  cpu->pcl[i] = '0';
	  return i;
	}else
	  cpu->pcl[i] = '1';
	i--;
  }
  i = 7;
  while(i>-1){
	if(cpu->pch[i]=='1'){
	  cpu->pch[i] = '0';
	  return i;
	}else
	  cpu->pch[i] = '1';
	i--;
  }
  return i;
  //  if(i==-1)
  //	printf("Error: PC reached End Of Memory");
}


