

#include "utils.h"
#include "../bigint.h"

#include <time.h>





int main(int argc, char** argv){

  if (argc>1){
    if (strcmp(argv[1],"add") == 0){
      printf("testing add\n");
      if (argc!=5){
        printf("./test_and_bench add 0x<hex of x> 0x<hex of y> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], y[NUM_LIMBS], expected[NUM_LIMBS], out[NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[4]+2);
      for (int i=0; i<NUM_ITERS; i++)
        FUNCNAME(add)(out,x,y);
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
    }
    else if (strcmp(argv[1],"addmod") == 0){
      printf("testing addmod\n");
      if (argc!=6){
        printf("./test_and_bench addmod 0x<hex of x> 0x<hex of y> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], y[NUM_LIMBS], mod[NUM_LIMBS], expected[NUM_LIMBS], out[NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)mod,argv[4]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[5]+2);
      struct timespec requestStart, requestEnd;
      clock_gettime(CLOCK_REALTIME, &requestStart);
      for (int i=0; i<NUM_ITERS; i++){
        FUNCNAME(addmod)(out,x,y,mod);
	//x[i%NUM_LIMBS] = out[NUM_LIMBS-1];
      }
      clock_gettime(CLOCK_REALTIME, &requestEnd);
      double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
                 + ( requestEnd.tv_nsec - requestStart.tv_nsec )
                 / 1E9;
      if (NUM_ITERS>1) printf( "execution time: %lf s\n", accum );
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
    }
    else if (strcmp (argv[1],"sub") == 0){
      printf("testing sub\n");
      if (argc!=5){
        printf("./test_and_bench sub 0x<hex of x> 0x<hex of y> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], y[NUM_LIMBS], expected[NUM_LIMBS], out[NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[4]+2);
      for (int i=0; i<NUM_ITERS; i++)
        FUNCNAME(sub)(out,x,y);
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
    }
    else if (strcmp(argv[1],"submod") == 0){
      printf("testing submod\n");
      if (argc!=6){
        printf("./test_and_bench submod 0x<hex of x> 0x<hex of y> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], y[NUM_LIMBS], mod[NUM_LIMBS], expected[NUM_LIMBS], out[NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)mod,argv[4]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[5]+2);
      for (int i=0; i<NUM_ITERS; i++)
        FUNCNAME(submod)(out,x,y,mod);
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
    }
    else if (strcmp (argv[1],"lessthan") == 0){
      printf("testing less_than\n");
      if (argc!=5){
        printf("./test_and_bench sub 0x<hex of x> 0x<hex of y> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], y[NUM_LIMBS];
      uint8_t expected, out;
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray(&expected,argv[4]+2);
      for (int i=0; i<NUM_ITERS; i++)
        out = FUNCNAME(less_than)(x,y);
      if (NUM_ITERS==1){
        if (expected != out)
          //printf("ERROR: less than failed. %u %u\n",expected,out);
          printf("ERROR: lessthan expected: %u and got: %u\n",expected, out);
        else
          printf("correct\n");
      }
    }
    else if (strcmp (argv[1],"lessthanequal") == 0){
      printf("testing less_than_or_equal\n");
      if (argc!=5){
        printf("./test_and_bench less_than_or_equal 0x<hex of x> 0x<hex of y> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], y[NUM_LIMBS];
      uint8_t expected, out;
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray(&expected,argv[4]+2);
      for (int i=0; i<NUM_ITERS; i++)
        out = FUNCNAME(less_than_or_equal)(x,y);
      if (NUM_ITERS==1){
        if (expected != out)
          //printf("ERROR: less than or equal failed.\n");
          printf("less_than_or_equal expected: %u and got: %u\n",expected, out);
        else
          printf("correct\n");
      }
    }
    else if (strcmp (argv[1],"mul") == 0){
      printf("testing mul\n");
      if (argc!=5){
        printf("./test_and_bench mul 0x<hex of x> 0x<hex of y> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], y[NUM_LIMBS], expected[2*NUM_LIMBS], out[2*NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[4]+2);
      for (int i=0; i<NUM_ITERS; i++)
        FUNCNAME(mul)(out,x,y);
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<2*NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
    }
    else if (strcmp (argv[1],"div") == 0){
      printf("testing div\n");
      if (argc!=6){
        printf("./test_and_bench div 0x<hex of x> 0x<hex of y> 0x<hex of expected quotient> 0x<hex of expected remainder>\n");
	return -1;
      }
      UINT x[NUM_LIMBS], y[NUM_LIMBS], outr_expected[NUM_LIMBS], outq_expected[NUM_LIMBS], outr[NUM_LIMBS], outq[NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)outq_expected,argv[4]+2);
      hexstr_to_bytearray((uint8_t*)outr_expected,argv[5]+2);
      for (int i=0; i<NUM_ITERS; i++)
        FUNCNAME(div)(outq,outr,x,y);
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<NUM_LIMBS; i++){
          if(outq[i]!=outq_expected[i]){
            printf("ERROR: outq[%d]=%lx and outq_expected[%d]=%lx\n",i,outq[i],i,outq_expected[i]);
            error=1;
          }
          if(outr[i]!=outr_expected[i]){
            printf("ERROR: outr[%d]=%lx and outr_expected[%d]=%lx\n",i,outr[i],i,outr_expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
    }
    else if (strcmp (argv[1],"square") == 0){
      printf("testing square\n");
      if (argc!=4){
        printf("./test_and_bench square 0x<hex of x> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], expected[2*NUM_LIMBS], out[2*NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[3]+2);
      for (int i=0; i<NUM_ITERS; i++)
        FUNCNAME(square)(out,x);
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<2*NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
    }
    else if (strcmp (argv[1],"montreduce") == 0){
      printf("testing montgomery reduce\n");
      if (argc!=6){
        printf("./test_and_bench montreduce 0x<hex of x> 0x<hex of mod> 0x<hex of modinv> 0x<hex of expected>\n");
        return -1;
      }

      UINT x[2*NUM_LIMBS], m[NUM_LIMBS], inv[NUM_LIMBS], expected[NUM_LIMBS], out[NUM_LIMBS];
      // init x with zeros, just in case arg is small
      for (int i=0; i<NUM_LIMBS*2; i++)
        x[i]=0;
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)m,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)inv,argv[4]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[5]+2);
      for (int i=0; i<NUM_ITERS; i++)
        FUNCNAME(montreduce)(out,x,m,((UINT*)inv)[0]);
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
    }
    else if (strcmp (argv[1],"mulmodmont") == 0){
      printf("testing montgomery multiplication\n");
      if (argc!=7){
        printf("./test_and_bench mulmodmont 0x<hex of x> 0x<hex of y> 0x<hex of mod> 0x<hex of modinv> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], y[NUM_LIMBS], m[NUM_LIMBS], inv[NUM_LIMBS], expected[NUM_LIMBS], out[NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)m,argv[4]+2);
      hexstr_to_bytearray((uint8_t*)inv,argv[5]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[6]+2);
      struct timespec requestStart, requestEnd;
      clock_gettime(CLOCK_REALTIME, &requestStart);
      for (int i=0; i<NUM_ITERS; i++){
        FUNCNAME(mulmodmont)(out,x,y,m,((UINT*)inv)[0]);
	x[i%NUM_LIMBS] = out[NUM_LIMBS-1];
      }
      clock_gettime(CLOCK_REALTIME, &requestEnd);
      double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
                 + ( requestEnd.tv_nsec - requestStart.tv_nsec )
                 / 1E9;
      if (NUM_ITERS>1) printf( "execution time: %lf s\n", accum );
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
      return out[0];
    }
    else if (strcmp (argv[1],"mulmodmontHAC") == 0){
      printf("testing montgomeryHAC multiplication\n");
      if (argc!=7){
        printf("./test_and_bench mulmodmontHAC 0x<hex of x> 0x<hex of y> 0x<hex of mod> 0x<hex of modinv> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], y[NUM_LIMBS], m[NUM_LIMBS], inv[NUM_LIMBS], expected[NUM_LIMBS], out[NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)m,argv[4]+2);
      hexstr_to_bytearray((uint8_t*)inv,argv[5]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[6]+2);
      struct timespec requestStart, requestEnd;
      clock_gettime(CLOCK_REALTIME, &requestStart);
      for (int i=0; i<NUM_ITERS; i++)
        FUNCNAME(mulmodmontHAC)(out,x,y,m,((UINT*)inv)[0]);
      clock_gettime(CLOCK_REALTIME, &requestEnd);
      double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
                 + ( requestEnd.tv_nsec - requestStart.tv_nsec )
                 / 1E9;
      if (NUM_ITERS>1) printf( "execution time: %lf s\n", accum );
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
      return out[0];
    }
    else if (strcmp (argv[1],"mulmodmontFIOS") == 0){
      printf("testing montgomeryFIOS multiplication\n");
      if (argc!=7){
        printf("./test_and_bench mulmodmontFIOS 0x<hex of x> 0x<hex of y> 0x<hex of mod> 0x<hex of modinv> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], y[NUM_LIMBS], m[NUM_LIMBS], inv[NUM_LIMBS], expected[NUM_LIMBS], out[NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)m,argv[4]+2);
      hexstr_to_bytearray((uint8_t*)inv,argv[5]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[6]+2);
      struct timespec requestStart, requestEnd;
      clock_gettime(CLOCK_REALTIME, &requestStart);
      for (int i=0; i<NUM_ITERS; i++)
        FUNCNAME(mulmodmontFIOS)(out,x,y,m,((UINT*)inv)[0]);
      clock_gettime(CLOCK_REALTIME, &requestEnd);
      double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
                 + ( requestEnd.tv_nsec - requestStart.tv_nsec )
                 / 1E9;
      if (NUM_ITERS>1) printf( "execution time: %lf s\n", accum );
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
      return out[0];
    }
    else if (strcmp (argv[1],"mulmodmontSOS") == 0){
      printf("testing montgomery multiplication SOS method\n");
      if (argc!=7){
        printf("./test_and_bench mulmodmontSOS 0x<hex of x> 0x<hex of y> 0x<hex of mod> 0x<hex of modinv> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], y[NUM_LIMBS], m[NUM_LIMBS], inv[NUM_LIMBS], expected[NUM_LIMBS], out[NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)m,argv[4]+2);
      hexstr_to_bytearray((uint8_t*)inv,argv[5]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[6]+2);
      struct timespec requestStart, requestEnd;
      clock_gettime(CLOCK_REALTIME, &requestStart);
      for (int i=0; i<NUM_ITERS; i++)
        FUNCNAME(mulmodmontSOS)(out,x,y,m,((UINT*)inv)[0]);
      clock_gettime(CLOCK_REALTIME, &requestEnd);
      double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
                 + ( requestEnd.tv_nsec - requestStart.tv_nsec )
                 / 1E9;
      if (NUM_ITERS>1) printf( "execution time: %lf s\n", accum );
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
    }
    else if (strcmp (argv[1],"mulmodmont384_asm") == 0){
      printf("testing montgomery multiplication 384-bit in assembly\n");
      if (argc!=7){
        printf("./test_and_bench mulmodmont384_asm 0x<hex of x> 0x<hex of y> 0x<hex of mod> 0x<hex of modinv> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], y[NUM_LIMBS], m[NUM_LIMBS], inv[NUM_LIMBS], expected[NUM_LIMBS], out[NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)m,argv[4]+2);
      hexstr_to_bytearray((uint8_t*)inv,argv[5]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[6]+2);
      struct timespec requestStart, requestEnd;
      clock_gettime(CLOCK_REALTIME, &requestStart);
      for (int i=0; i<NUM_ITERS; i++)
        mulmodmontCIOSasm384(out,x,y,m,((UINT*)inv)[0]);
      clock_gettime(CLOCK_REALTIME, &requestEnd);
      double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
                 + ( requestEnd.tv_nsec - requestStart.tv_nsec )
                 / 1E9;
      if (NUM_ITERS>1) printf( "execution time: %lf s\n", accum );
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
    }
    else if (strcmp (argv[1],"montsquare") == 0){
      printf("testing montgomery square\n");
      if (argc!=6){
        printf("./test_and_bench montsquare 0x<hex of x> 0x<hex of mod> 0x<hex of modinv> 0x<hex of expected>\n");
        return -1;
      }

      UINT x[NUM_LIMBS], m[NUM_LIMBS], inv[NUM_LIMBS], expected[NUM_LIMBS], out[NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)m,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)inv,argv[4]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[5]+2);
      for (int i=0; i<NUM_ITERS; i++)
        FUNCNAME(montsquare)(out,x,m,((UINT*)inv)[0]);
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
    }
    else if (strcmp (argv[1],"mulmod_oddmod") == 0){
      printf("testing mulmod_oddmod\n");
      if (argc!=7){
        printf("./test_and_bench mulmod_oddmod 0x<hex of x> 0x<hex of y> 0x<hex of mod> 0x<hex of modinv> 0x<hex of expected>\n");
	return -1;
      }

      UINT x[NUM_LIMBS], y[NUM_LIMBS], m[NUM_LIMBS], inv[NUM_LIMBS], expected[NUM_LIMBS], out[NUM_LIMBS];
      hexstr_to_bytearray((uint8_t*)x,argv[2]+2);
      hexstr_to_bytearray((uint8_t*)y,argv[3]+2);
      hexstr_to_bytearray((uint8_t*)m,argv[4]+2);
      hexstr_to_bytearray((uint8_t*)inv,argv[5]+2);
      hexstr_to_bytearray((uint8_t*)expected,argv[6]+2);
      for (int i=0; i<NUM_ITERS; i++){
        FUNCNAME(mulmodmont)(out,x,y,m,((UINT*)inv)[0]);
      }
      if (NUM_ITERS==1){
        int error=0;
        for (int i=0; i<NUM_LIMBS; i++){
          if(out[i]!=expected[i]){
            printf("ERROR: out[%d]=%lx and expected[%d]=%lx\n",i,out[i],i,expected[i]);
            error=1;
          }
        }
        if (!error){ printf("correct\n");}
      }
    }
    else {
      printf("./test_and_bench <testname> ...\n");
      printf("    where <testname> is mulmodmont, add, sub, etc.\n");
    }
  }
}
