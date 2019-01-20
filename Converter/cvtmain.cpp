 /** 
	NAME:
     input: ERP video name
     video name format: description_widthxheight_yuv420_framesize.yuv

     output: cfg file from ERP to 10 different projections with bat file to automatic execution
	 outputVideoName format: format_widthxheight_30Hz_8b_420.yuv
	
	 convert_cfg name format: 
						360convert_ERP_dest_test.cfg
	 test_cfg name format: 
						360test_test_sequence.cfg
	 bat format:
						format_widthxheight.bat
	DIRECTORY:
	 360Lib exe firectory:
						C:\hm-360lib\HM-16.16\bin\vc2015\x64\Debug\Test\convert
	 sequence outputdirectory: 
						C:\VRTest\sequence_cvt\DESCRIPTION\
	 sequence inputdirectory:
						C:\VRTest\sequence
	 cfg and bat outputdirectory:
						C:\VRTest\ERP_DEST
 */

#include"CvtConfigGenerator.h"
int main(int argc, char* args[]) {
	CvtConfigGenerator cvtGenerator(args[1]);

}