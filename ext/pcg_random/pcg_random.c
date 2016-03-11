#include <pcg_variants.h>

#include "pcg_random.h"
#include "includes/oneseq.h"
#include "includes/setseq.h"
#include "includes/mcg.h"
#include "includes/unique.h"

VALUE rb_mPcgRandom;
/*
https://github.com/imneme/pcg-c/blob/master/include/pcg_variants.h#L846
*/
void
Init_pcg_random(void)
{
  rb_mPcgRandom = rb_define_module("PcgRandom");
}
