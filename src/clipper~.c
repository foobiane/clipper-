#include "m_pd.h"

#include <math.h>

typedef struct _clipper {
    t_object obj;
    float cutoff;
    float fsig;
} t_clipper;

void clipper_tilde_setup(void);
void* clipper_new(t_floatarg f);
void clipper_dsp(t_clipper* x, t_signal** sp);
t_int* clipper_perform(t_int* w);

float fsign(float x);

static t_class* clipper_class;

void clipper_tilde_setup(void) {
    clipper_class = class_new(
        gensym("clipper~"),         // Name
        (t_newmethod) clipper_new,  // Constructor
        NULL,                       // Destructor (unused)
        sizeof(t_clipper),          // Size
        CLASS_DEFAULT,              // Graphical representation
        A_DEFFLOAT,                 // Data input format
        0                           
    );

    CLASS_MAINSIGNALIN(clipper_class, t_clipper, fsig);
    class_addmethod(clipper_class, (t_method) clipper_dsp, gensym("dsp"), A_CANT, 0);	
}

void* clipper_new(t_floatarg f) {
    t_clipper* x = (t_clipper*) pd_new(clipper_class);
    
    outlet_new(&x->obj, gensym("signal"));
    x->cutoff = f; // TODO: dB to float conversion?

    return x;
}

void clipper_dsp(t_clipper* x, t_signal** sp) {
    if (sp[0]->s_sr > 0)
        dsp_add(clipper_perform, 4, x, sp[0]->s_vec /* Left inlet */, sp[1]->s_vec /* Outlet */, sp[1]->s_n /* Signal vector size */);
}

t_int* clipper_perform(t_int* w) {
    t_clipper* x = (t_clipper*) w[1];
    float* in = (float*) w[2];
    float* out = (float*) w[3];
    int n = w[4];

    while (n--) {
        *out = (fabs(*in) > x->cutoff ? fsign(*in) * x->cutoff : *in);
        out++; in++;
    }

    return w + 5;
}

// Returns the sign of a float value.
float fsign(float x) {
    return (x > 0) - (x < 0);
}