/*
 *Wab launcher V2.5 the original :=)
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
#define printf	pspDebugScreenPrintf

#define DPRINT    pspDebugScreenPrintf

#define PIXELSIZE   1
#define LINESIZE    512

int blocked = 1;
ctrl_data_t pad;

#define GAME_PATH  "fatms:/PSP_GAME/SYSDIR/BOOT.BIN"

#define GAME_PATH_DEST  "fatms:/PSP_GAME/SYSDIR/PATCHED_BOOT.BIN"

char *pg_vramtop=(char *)0x04000000;

PSP_MODULE_INFO("LauncherV2_5", 0x1000, 1, 1);   // 0x1000 = Kernel MODE
PSP_MAIN_THREAD_ATTR(0); // 0 for kernel mode too


char *pgGetVramAddr(unsigned long x,unsigned long y)
{
	return pg_vramtop+x*2+y*512*2+0x40000000;
}

//Screenshot in game 
void ScrenshotCode(const char* zfiles)
{ //from Weak 
unsigned char bmpHeader24[] = { 0x42, 0x4d, 0x38, 0xfa, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x10, 0x01, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; 
unsigned char buffer[480*3]; 
unsigned char  r,g,b; 
int bufferIndex = 0; 
unsigned short p; 
int file;
int i,e;
unsigned char *vptr0;
unsigned char *vptr;

file = sceIoOpen(zfiles,PSP_O_CREAT | PSP_O_TRUNC | PSP_O_RDWR, 0777); // savePath should hold the path to your file 

// write bmp header 
sceIoWrite(file,bmpHeader24,54); 

// write bmp data 
vptr0 = pgGetVramAddr(1,0); 
for(i=0; i<272; i++) 
{ 
vptr=vptr0; 
for(e=0; e<480; e++) 
{ 
    p = *(unsigned short *)vptr; 
    r = (p<<3)&0xf8; 
    g = (p>>2)&0xf8; 
    b = (p>>7)&0xf8;          
          
    buffer[bufferIndex] = b; 
    bufferIndex++;          
    buffer[bufferIndex] = g; 
    bufferIndex++;          
    buffer[bufferIndex] = r; 
    bufferIndex++; 

vptr+=PIXELSIZE*2; 
} 
// write chunk 
sceIoWrite(file,buffer,480*3); 
bufferIndex=0; 
vptr0-=LINESIZE*2; 
} 

// bmp end 
unsigned char end[] = { 0x00, 0x00 }; 
sceIoWrite(file,end,2); 

sceIoClose(file); 
}
//Yoshihiro Screenshot number genarator 

int ScrenshotGen() 
{ 
int fd; 
char filename[56]; 
int i;
sceIoMkdir("ms0:/psp/game/Screenshot", 0);
for(i=0; i<2000; i++) 
{ 
sprintf(filename, "ms0:/psp/game/Screenshot/screenshot%03d.bmp", i); 
fd = sceIoOpen(filename,PSP_O_RDONLY,0); 
if(fd < 0) 
{ 
break; 
} 
sceIoClose(fd); 
} 
//Your string for make screenshot 
ScrenshotCode( filename); 
return 0; 
} 


void loadModules()
{
	int module = 0;
	
     // Never load rinit.prx that can be damage your psp 

	module = sceKernelLoadModule("ms0:/common/prx/audiocodec.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
      module = sceKernelLoadModule("ms0:/common/prx/cert_loader.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/ifhandle.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/libadler.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/libatrac3plus.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/libbase64.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/libfont.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/libfpu.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/libhttp.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/libmt19937.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/libnetcnf.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/libparse_http.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/libparse_uri.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/libqpcode.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/libssl.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/memab.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/mpegbase.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/mpeg.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/psmf.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/pspnet_adhoc_auth.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/pspnet_adhocctl.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/pspnet_adhoc_download.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/pspnet_adhoc_matching.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/pspnet_ap_dialog_dummy.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/pspnet_adhoc.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/pspnet_apctl.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/pspnet_ap_dialog_dummy.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/pspnet_inet.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/pspnet.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/pspnet_resolver.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/scan.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/sc_sascore.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/show_macaddr.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/usbpspcm.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
	module = sceKernelLoadModule("ms0:/common/prx/videocodec.prx", 0, 0);
	sceKernelStartModule(module, 0, 0, 0, 0);
}


//Yoshihiro auto patcher 
//all nids for NBA 2K5 is from PSPDEV NBA 2K5 only
void patcher(void) {
 	int source, target;
 	int lFileLength, i;
      pspDebugScreenPrintf("Patch boot.bin wait please \n");
      
      char szSearch[] = "disc0:/";
      char szSearch2[] = "disc0:"; 
      char szSearch3[] = "disc0"; 
      char szString2[] = { 0x00 ,0x00, 0x00, 0x00 };
      char szString12[] = { 0xEC ,0xC1, 0xF0, 0x50 };
      char szString3[] = { 0x86 ,0xE3, 0x7D, 0x97 };
      char szString4[] = { 0xEC ,0xC1, 0xF0, 0x2A };
      char szString5[] = { 0x2A ,0x98, 0xFF, 0xD1 }; //sceKernelStopModule
      char szString6[] = { 0xCE ,0x8F, 0xF0, 0x8E }; //sceUmdWaitDriveStat
      char szString7[] = { 0x29 ,0xb7, 0xeb, 0x46 }; //sceUmdCheckMedium
      char szString8[] = { 0x6c ,0x14, 0x4a, 0x6b }; //sceUmdGetDriveStat
      char szString10[] = { 0x4d,0x40,0xe7,0xae }; //sceUmdRegisterUMDCallBack
      char szString11[] = { 0x47,0x3d,0x18,0xc6 }; //sceUmdActivate



      char *szBuffer;
 
      // if the PATCHED_BOOT.BIN not exist jump directely to game load
      if(sceIoOpen(GAME_PATH_DEST,PSP_O_RDONLY , 0) <0)
      {
 	source = sceIoOpen(GAME_PATH,PSP_O_RDONLY , 0);
 	sceIoLseek(source,0,PSP_SEEK_END);
 	lFileLength = sceIoLseek(source,0,PSP_SEEK_END);
 	sceIoLseek(source,0,PSP_SEEK_SET);
 	szBuffer = (char *)malloc(lFileLength);
 	target = sceIoOpen(GAME_PATH_DEST,PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);

 	sceIoRead(source, szBuffer, lFileLength);

      	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString3, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : 0x86E37D97   \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

   	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString4, 4) == 0) {
                 pspDebugScreenPrintf("found and kill Nids : 0xECC1F02A   \n");        
                 memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

   	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString5, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceKernelStopModule \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}


	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString12, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceKernelStopModule \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

 

         	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString6, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceUmdWaitDriveStat \n"); 
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

   
       	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString7, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceUmdCheckMedium \n" ); 
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}


 	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString8, 4) == 0) {
                        memcpy(&szBuffer[i], szString10, 4);
                               
             }
 		
	}

 	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString11, 4) == 0) {
                pspDebugScreenPrintf("found and kill Nids : sceUmdActivate \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

	for(i = 0; i < (lFileLength -7) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch, strlen(szSearch)) == 0) {
                        pspDebugScreenPrintf("found and replace : disc0:/ by fatms:/ \n");	
                        memcpy(&szBuffer[i], "fatms:/", strlen("fatms:/"));
                               
             }
 		
 	}
 
     for(i = 0; i < (lFileLength -6) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch2, strlen(szSearch2)) == 0) {
                        pspDebugScreenPrintf("found and replace : disc0: by fatms: \n");	
                        memcpy(&szBuffer[i], "fatms:", strlen("fatms:"));
                               
             }
 		
 	}



        for(i = 0; i < (lFileLength -5) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch3, strlen(szSearch3)) == 0) {
                        pspDebugScreenPrintf("found and replace : disc0 by fatms \n");	
                        memcpy(&szBuffer[i], "fatms", strlen("fatms"));
                               
             }
 		
 	}



            sceIoWrite(target,szBuffer ,lFileLength);
    	sceIoClose(target);
      sceIoClose(source);
	free(szBuffer);
   }
       pspDebugScreenPrintf("patch finish start game \n");	
        int exec_p = sceKernelLoadModule(GAME_PATH_DEST, 0, 0);
	sceKernelStartModule(exec_p, 0, 0, 0, 0);

}

// Methode B for Ape escape
void patcher2(void) {
 	int source, target;
 	int lFileLength, i;
      pspDebugScreenPrintf("Patch boot.bin wait please \n");
      
      char szSearch[] = "disc0:/";
      char szSearch2[] = "disc0:"; 
      char szSearch3[] = "disc0"; 
      char szString2[] = { 0x00 ,0x00, 0x00, 0x00 };
      char szString14[] = {  0x29 ,0x5e,0x9e,0x4a };
      char szString12[] = { 0xEC ,0xC1, 0xF0, 0x50 };
      char szString3[] = { 0x86 ,0xE3, 0x7D, 0x97 };
      char szString4[] = { 0xEC ,0xC1, 0xF0, 0x2A };
      char szString5[] = { 0x2A ,0x98, 0xFF, 0xD1 }; //sceKernelStopModule
      char szString6[] = { 0xCE ,0x8F, 0xF0, 0x8E }; //sceUmdWaitDriveStat
      char szString7[] = { 0x29 ,0xb7, 0xeb, 0x46 }; //sceUmdCheckMedium
      char szString15[] = { 0xB8 ,0xEB, 0x75, 0xD6 };
      char szString13[] = {  0xAA,0x11,0x09,0x2E };  
      char szString11[] = { 0x47,0x3d,0x18,0xc6 }; //sceUmdActivate


      char *szBuffer;
  
      // if the PATCHED_BOOT.BIN not exist jump directely to game load
      if(sceIoOpen(GAME_PATH_DEST,PSP_O_RDONLY , 0) <0)
      {
 	source = sceIoOpen(GAME_PATH,PSP_O_RDONLY , 0);
 	sceIoLseek(source,0,PSP_SEEK_END);
 	lFileLength = sceIoLseek(source,0,PSP_SEEK_END);
 	sceIoLseek(source,0,PSP_SEEK_SET);
 	szBuffer = (char *)malloc(lFileLength);
 	target = sceIoOpen(GAME_PATH_DEST,PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);

 	sceIoRead(source, szBuffer, lFileLength);

      	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString3, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : 0x86E37D97   \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

   	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString4, 4) == 0) {
                 pspDebugScreenPrintf("found and kill Nids : 0xECC1F02A   \n");        
                 memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

   	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString5, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceKernelStopModule \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}


	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString12, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceKernelStopModule \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

 

         	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString6, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceUmdWaitDriveStat \n"); 
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

   
       	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString7, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceUmdCheckMedium \n" ); 
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}


       	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString13, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceUmdCheckMedium \n" ); 
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}


	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString15, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceUmdCheckMedium \n" ); 
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}



 	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString11, 4) == 0) {
                pspDebugScreenPrintf("found and kill Nids : sceUmdActivate \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

   for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString14, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceUmdWaitDriveStatCB \n" ); 
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}


	for(i = 0; i < (lFileLength -7) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch, strlen(szSearch)) == 0) {
                        pspDebugScreenPrintf("found and replace : disc0:/ by fatms:/ \n");	
                        memcpy(&szBuffer[i], "fatms:/", strlen("fatms:/"));
                               
             }
 		
 	}
 
     for(i = 0; i < (lFileLength -6) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch2, strlen(szSearch2)) == 0) {
                        pspDebugScreenPrintf("found and replace : disc0: by fatms: \n");	
                        memcpy(&szBuffer[i], "fatms:", strlen("fatms:"));
                               
             }
 		
 	}



        for(i = 0; i < (lFileLength -5) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch3, strlen(szSearch3)) == 0) {
                        pspDebugScreenPrintf("found and replace : disc0 by fatms \n");	
                        memcpy(&szBuffer[i], "fatms", strlen("fatms"));
                               
             }
 		
 	}



      sceIoWrite(target,szBuffer ,lFileLength);
    	sceIoClose(target);
      sceIoClose(source);
	free(szBuffer);
   }
      pspDebugScreenPrintf("patch finish start game \n");	
      int exec_p = sceKernelLoadModule(GAME_PATH_DEST, 0, 0);
	sceKernelStartModule(exec_p, 0, 0, 0, 0);
       

}

//NHL 2K5 ^_^
void patcher3(void) {
 	int source, target;
 	int lFileLength, i;
      pspDebugScreenPrintf("Patch boot.bin wait please \n");
      
      char szSearch[] = "disc0:/";
      char szString2[] = { 0x00 ,0x00, 0x00, 0x00 };
      char szString14[] = {  0x29 ,0x5e,0x9e,0x4a };
      char szString12[] = { 0xEC ,0xC1, 0xF0, 0x50 };
      char szString3[] = { 0x86 ,0xE3, 0x7D, 0x97 };
      char szString4[] = { 0xEC ,0xC1, 0xF0, 0x2A };
      char szString5[] = { 0x2A ,0x98, 0xFF, 0xD1 }; //sceKernelStopModule
      char szString6[] = { 0xCE ,0x8F, 0xF0, 0x8E }; //sceUmdWaitDriveStat
      char szString7[] = { 0x29 ,0xb7, 0xeb, 0x46 }; //sceUmdCheckMedium
      char szString15[] = { 0xB8 ,0xEB, 0x75, 0xD6 };
      char szString13[] = {  0xAA,0x11,0x09,0x2E };  
   
      char *szBuffer;

      // if the PATCHED_BOOT.BIN not exist jump directely to game load
      if(sceIoOpen(GAME_PATH_DEST,PSP_O_RDONLY , 0) <0)
      {
 	source = sceIoOpen(GAME_PATH,PSP_O_RDONLY , 0);
 	sceIoLseek(source,0,PSP_SEEK_END);
 	lFileLength = sceIoLseek(source,0,PSP_SEEK_END);
 	sceIoLseek(source,0,PSP_SEEK_SET);
 	szBuffer = (char *)malloc(lFileLength);
 	target = sceIoOpen(GAME_PATH_DEST,PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);

 	sceIoRead(source, szBuffer, lFileLength);

      	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString3, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : 0x86E37D97   \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

   	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString4, 4) == 0) {
                 pspDebugScreenPrintf("found and kill Nids : 0xECC1F02A   \n");        
                 memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

   	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString5, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceKernelStopModule \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}


	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString12, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceKernelStopModule \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

  
       	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString7, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceUmdCheckMedium \n" ); 
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}


  	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString6, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceUmdCheckMedium \n" ); 
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}


       	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString13, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceUmdCheckMedium \n" ); 
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}


	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString14, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceUmdWaitDriveStatCB \n" ); 
                        memcpy(&szBuffer[i], szString2, 4);
      
               }
 		
 	}
     

	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString15, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceUmdCheckMedium \n" ); 
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}



 	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString7, 4) == 0) {
               pspDebugScreenPrintf("found and kill Nids : sceUmdGetErrorStat" );
               memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

   for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString14, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : sceUmdWaitDriveStatCB \n" ); 
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}


	for(i = 0; i < (lFileLength -7) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch, strlen(szSearch)) == 0) {
                        pspDebugScreenPrintf("found and replace : disc0:/ by fatms:/ \n");	
                        memcpy(&szBuffer[i], "fatms:/", strlen("fatms:/"));
                               
             }
 		
 	}
 
      sceIoWrite(target,szBuffer ,lFileLength);
    	sceIoClose(target);
      sceIoClose(source);
	free(szBuffer);
   }
       pspDebugScreenPrintf("patch finish start game \n");	
       int exec_p = sceKernelLoadModule(GAME_PATH_DEST, 0, 0);
	sceKernelStartModule(exec_p, 0, 0, 0, 0);
       

}

//Wipeout ^_^
void patcher4(void) {
 	int source, target;
 	int lFileLength, i;
      pspDebugScreenPrintf("Patch boot.bin wait please \n");
      
      char szSearch[] = "disc0:/PSP_GAME";
      char szSearch2[] = { 0x64,0x69,0x73,0x63,0x30,0x3A,0x5C}; 
      char szSearch3[] = { 0x66,0x61,0x74,0x6D,0x73,0x3A,0x5C};
      char szString[] =  {  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
      char szString2[] = {  0x29,0xB7,0xEB,0x46,0x47,0x3D,0x18,0xC6,0xCE,0x8F,0xF0,0x8E };
      char szString3[] = {  0x86,0xE3,0x7D,0x97,0xEC,0xC1,0xF0,0x50,0x2A,0x98,0xFF,0xD1,0xAA,0x11,0x09,0x2E };
      char szString4[] = {  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
      char *szBuffer;
      

      // if the PATCHED_BOOT.BIN not exist jump directely to game load
      if(sceIoOpen(GAME_PATH_DEST,PSP_O_RDONLY , 0) <0)
      {
 	source = sceIoOpen(GAME_PATH,PSP_O_RDONLY , 0);
 	sceIoLseek(source,0,PSP_SEEK_END);
 	lFileLength = sceIoLseek(source,0,PSP_SEEK_END);
 	sceIoLseek(source,0,PSP_SEEK_SET);
 	szBuffer = (char *)malloc(lFileLength);
 	target = sceIoOpen(GAME_PATH_DEST,PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);

 	sceIoRead(source, szBuffer, lFileLength);

      	for(i = 0; i < (lFileLength -12) ; i++) {
 		if(memcmp(&szBuffer[i], szString2, 12) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : Nids hack   \n");
                        memcpy(&szBuffer[i], szString, 12);
                               
             }
 		
 	}

   	for(i = 0; i < (lFileLength -16) ; i++) {
 		if(memcmp(&szBuffer[i], szString3, 16) == 0) {
                 pspDebugScreenPrintf("found and kill Nids : Nids hack   \n");        
                 memcpy(&szBuffer[i], szString4, 16);
                               
             }
 		
 	}



for(i = 0; i < (lFileLength -7) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch2, 7) == 0) {
                        pspDebugScreenPrintf("found and replace : disc0: by fatms: \n");	
                        memcpy(&szBuffer[i], szSearch3 , 7);
                               
             }
 		
 	}




        for(i = 0; i < (lFileLength -15) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch, strlen(szSearch)) == 0) {
                        pspDebugScreenPrintf("found and replace : disc0 by fatms \n");	
                        memcpy(&szBuffer[i], "fatms:/PSP_GAME", strlen("fatms:/PSP_GAME"));
                               
             }
 		
 	}



            sceIoWrite(target,szBuffer ,lFileLength);
    	sceIoClose(target);
      sceIoClose(source);
	free(szBuffer);
   }
       pspDebugScreenPrintf("patch finish start game \n");	
        int exec_p = sceKernelLoadModule(GAME_PATH_DEST, 0, 0);
	sceKernelStartModule(exec_p, 0, 0, 0, 0);
       

}

// coded arms ^_^
void patcher5(void) {
 	int source, target;
 	int lFileLength, i;
      pspDebugScreenPrintf("Patch boot.bin wait please \n");
      
      char szSearch[] = "disc0:/";
      char szSearch4[] = {0x3E,0xB2,0x08,0x0C};
      char szSearch5[] = {0x3A,0xB2,0x08,0x0C};
      char szSearch6[] = {0x3C,0xB2,0x08,0x0C};
      char szSearch9[] = { 0x66,0x61,0x74,0x6D,0x73,0x00 }; 
      char szSearch10[] =  { 0x64,0x69,0x73,0x63,0x30,0x00 };
      char szSearch7[] = { 0x86,0xE3,0x7D,0x97,0xEC,0xC1,0xF0,0x50,0xAA,0x11,0x09,0x2E };
      char szSearch8[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
      char szString2[] = { 0x00 ,0x00, 0x00, 0x00 };
  
     char *szBuffer;
      

      // if the PATCHED_BOOT.BIN not exist jump directely to game load
      if(sceIoOpen(GAME_PATH_DEST,PSP_O_RDONLY , 0) <0)
      {
 	source = sceIoOpen(GAME_PATH,PSP_O_RDONLY , 0);
 	sceIoLseek(source,0,PSP_SEEK_END);
 	lFileLength = sceIoLseek(source,0,PSP_SEEK_END);
 	sceIoLseek(source,0,PSP_SEEK_SET);
 	szBuffer = (char *)malloc(lFileLength);
 	target = sceIoOpen(GAME_PATH_DEST,PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);

 	sceIoRead(source, szBuffer, lFileLength);

      	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch4, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : Nids hack   \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}
 
	for(i = 0; i < (lFileLength -6) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch10, 6) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : Magic \n");
                        memcpy(&szBuffer[i], szSearch9, 6);
                               
             }
 		
 	}

   	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch5, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : Nids hack   \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}

      for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch6, 4) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : Nids hack   \n");
                        memcpy(&szBuffer[i], szString2, 4);
                               
             }
 		
 	}
/*
 	for(i = 0; i < (lFileLength -4) ; i++) {
 		if(memcmp(&szBuffer[i], szString8, 4) == 0) {
                        memcpy(&szBuffer[i], szString10, 4);
                        pspDebugScreenPrintf("found and kill Nids : WAB NO UMD\n");

                               
             }
 		
	}
*/

    for(i = 0; i < (lFileLength -12) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch7, 12) == 0) {
                        pspDebugScreenPrintf("found and kill Nids : Nids hack   \n");
                        memcpy(&szBuffer[i], szSearch8, 4);
                               
             }
 		
 	}


        for(i = 0; i < (lFileLength -7) ; i++) {
 		if(memcmp(&szBuffer[i], szSearch, strlen(szSearch)) == 0) {
                        pspDebugScreenPrintf("found and replace : disc0 by fatms \n");	
                        memcpy(&szBuffer[i], "fatms:/", strlen("fatms:/"));
                               
             }
 		
 	}



            sceIoWrite(target,szBuffer ,lFileLength);
    	sceIoClose(target);
      sceIoClose(source);
	free(szBuffer);
   }
      pspDebugScreenPrintf("patch finish start game \n");	
      int exec_p = sceKernelLoadModule(GAME_PATH_DEST, 0, 0);
	sceKernelStartModule(exec_p, 0, 0, 0, 0);
       

}



int main(void)
{  
   sceCtrlSetSamplingCycle( 0 );
   sceCtrlSetSamplingMode( 0 );
   pspDebugScreenInit();
   pspDebugScreenPrintf("WAB Team present the 2.5c for wait the V3.0 soon \n");
   sceKernelDelayThread(1000000);
   pspDebugScreenPrintf("Press CROSS for patch with Methode A original V2.5 \n");
   pspDebugScreenPrintf("Press CIRCLE for patch with Methode B compatible ape escape \n");
   pspDebugScreenPrintf("Press TRIANGLE for patch with Methode C compatible NHL 2K5  \n");
   pspDebugScreenPrintf("Press SQUARE for patch with Methode D compatible Wipeout  \n");
   pspDebugScreenPrintf("Press START for patch with Methode E compatible Coded Arms  \n");
   pspDebugScreenPrintf("Remenber you need delete the PATCHED_BOOT.BIN before test another methode  \n");

while(blocked)
{

 sceCtrlReadBufferPositive(&pad, 1);
 
   if(pad.buttons & CTRL_CROSS)
   {
    loadModules(); 
    patcher(); 
    return blocked == 0;
   }
   
   if(pad.buttons & CTRL_CIRCLE)
   {
    loadModules(); 
    patcher2(); 	
    return blocked == 0; 
  }

  if(pad.buttons & CTRL_TRIANGLE)
   {
    loadModules(); 
    patcher3(); 	
    return blocked == 0; 
  }

if(pad.buttons & CTRL_SQUARE
)
   {
    loadModules(); 
    patcher4(); 	
    return blocked == 0; 
  }
if(pad.buttons & CTRL_START)
   {
    loadModules(); 
    patcher5(); 	
    return blocked == 0; 
  }
 }
 
   return 0;
}
