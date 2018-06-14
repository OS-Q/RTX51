
struct time  {                        /* structure of the time record         */
  unsigned char hour;                 /* hour                                 */
  unsigned char min;                  /* minute                               */
  unsigned char sec;                  /* second                               */
};
sbit tta=P3^1;
sbit D1=P1^0;