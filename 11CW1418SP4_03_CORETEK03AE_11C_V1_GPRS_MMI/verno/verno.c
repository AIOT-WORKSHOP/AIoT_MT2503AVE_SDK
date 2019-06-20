#include "kal_release.h" 
kal_char* release_verno(void) 
{ 
   static kal_char verno_str[] = "SPROCOMM_ofoV1.0.9"; 
   return verno_str; 
} 
kal_char* release_hal_verno(void) 
{ 
   static kal_char hal_verno_str[] = ""; 
   return hal_verno_str; 
} 
kal_char* release_hw_ver(void) 
{ 
   static kal_char hw_ver_str[] = "SPROCOMM_MERCURY_V01"; 
   return hw_ver_str; 
} 
kal_char* build_date_time(void) 
{ 
   static kal_char build_date_time_str[] = "20190604-2015"; 
   return build_date_time_str; 
} 
kal_char* release_build(void) 
{ 
   static kal_char build_str[] = "BUILD_NO"; 
   return build_str; 
} 
kal_char* release_branch(void) 
{ 
   static kal_char build_branch_str[] = "11CW1418SP4_03 CORETEK03AE_11C"; 
   return build_branch_str; 
} 
kal_char* release_flavor(void) 
{ 
   static kal_char build_flavor_str[] = "NONE"; 
   return build_flavor_str; 
} 
kal_char* release_platform(void) 
{ 
   static kal_char release_platform_str[] = "MT2502"; 
   return release_platform_str; 
} 
kal_char* release_mmi_base(void) 
{ 
   static kal_char release_mmi_base_str[] = "PLUTO_MMI"; 
   return release_mmi_base_str; 
} 
kal_char* release_mmi_ver(void) 
{ 
   static kal_char release_mmi_ver_str[] = "PLUTO_MMI"; 
   return release_mmi_ver_str; 
} 
