/**
 * mruby-research
 */

#include <stdio.h>
#include <mruby.h>
#include <mruby/value.h>
#include <mruby/hash.h>
#include <mruby/proc.h>
#include <mruby/irep.h>
#include <mruby/string.h>
#include <mruby/array.h>
#include <mruby/variable.h>
#include <mruby/class.h>
#include <mruby/khash.h>
#include <mruby/data.h>
#include "defmrbconf.h"

struct vtypes {
  enum mrb_vtype tt;
  const char *name;
} vtypelist [] = {
  {MRB_TT_FALSE,     "MRB_TT_FALSE"},
  {MRB_TT_FREE,      "MRB_TT_FREE"},
  {MRB_TT_TRUE,      "MRB_TT_TRUE"},
  {MRB_TT_FIXNUM,    "MRB_TT_FIXNUM"},
  {MRB_TT_SYMBOL,    "MRB_TT_SYMBOL"},
  {MRB_TT_UNDEF,     "MRB_TT_UNDEF"},
  {MRB_TT_FLOAT,     "MRB_TT_FLOAT"},
  {MRB_TT_CPTR,      "MRB_TT_CPTR"},
  {MRB_TT_OBJECT,    "MRB_TT_OBJECT"},
  {MRB_TT_CLASS,     "MRB_TT_CLASS"},
  {MRB_TT_MODULE,    "MRB_TT_MODULE"},
  {MRB_TT_ICLASS,    "MRB_TT_ICLASS"},
  {MRB_TT_SCLASS,    "MRB_TT_SCLASS"},
  {MRB_TT_PROC,      "MRB_TT_PROC"},
  {MRB_TT_ARRAY,     "MRB_TT_ARRAY"},
  {MRB_TT_HASH,      "MRB_TT_HASH"},
  {MRB_TT_STRING,    "MRB_TT_STRING"},
  {MRB_TT_RANGE,     "MRB_TT_RANGE"},
  {MRB_TT_EXCEPTION, "MRB_TT_EXCEPTION"},
  {MRB_TT_FILE,      "MRB_TT_FILE"},
  {MRB_TT_ENV,       "MRB_TT_ENV"},
  {MRB_TT_DATA,      "MRB_TT_DATA"},
  {MRB_TT_FIBER,     "MRB_TT_FIBER"},
  {MRB_TT_MAXDEFINE, NULL},
};

struct colors {
  uint32_t color:3;
  const char *name;
} colorlist [] = {
  {0, "MRB_GC_GRAY"},
  {1, "MRB_GC_WHITE_A"},
  {2, "MRB_GC_WHITE_B"},
  {3, "MRB_GC_WHITES"},
  {4, "MRB_GC_BLACK"},
  {5, NULL},
};

struct fiber_states {
  enum mrb_fiber_state state;
  const char *name;
} fiber_state_list [] = {
  {MRB_FIBER_CREATED, "MRB_FIBER_CREATED"},
  {MRB_FIBER_RUNNING, "MRB_FIBER_RUNNING"},
#if MRUBY_RELEASE_NO >= 10300
  {MRB_FIBER_RESUMED, "MRB_FIBER_RESUMED"},
#else
  {MRB_FIBER_RESUMING, "MRB_FIBER_RESUMING"},
#endif
  {MRB_FIBER_SUSPENDED, "MRB_FIBER_SUSPENDED"},
  {MRB_FIBER_TRANSFERRED, "MRB_FIBER_TRANSFERRED"},
  {MRB_FIBER_TERMINATED, "MRB_FIBER_TERMINATED"}
};

static const char*
tt2str(enum mrb_vtype tt)
{
  struct vtypes *vs;

  for (vs = vtypelist; vs->name; vs++) {
    if (vs->tt == tt)
      return vs->name;
  }
  return NULL;
}

static const char*
color2str(uint32_t color)
{
  struct colors *cs;

  for (cs = colorlist; cs->name; cs++) {
    if (cs->color == color)
      return cs->name;
  }
  return NULL;
}

static const char*
fiber_state2str(enum mrb_fiber_state s)
{
  struct fiber_states *fs;

  for (fs = fiber_state_list; fs->name; fs++) {
    if (fs->state == s)
      return fs->name;
  }
  return NULL;
}

static mrb_value
mrb_class_s_mrbconf(mrb_state *mrb, mrb_value mod)
{
  mrb_value h = mrb_hash_new(mrb);
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_USE_FLOAT"), mrb_bool_value(DEF_MRB_USE_FLOAT));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_INT16"), mrb_bool_value(DEF_MRB_INT16));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_INT64"), mrb_bool_value(DEF_MRB_INT64));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_NAN_BOXING"), mrb_bool_value(DEF_MRB_NAN_BOXING));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_ENDIAN_BIG"), mrb_bool_value(DEF_MRB_ENDIAN_BIG));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_WORD_BOXING"), mrb_bool_value(DEF_MRB_WORD_BOXING));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_FUNCALL_ARGC_MAX"), mrb_fixnum_value(MRB_FUNCALL_ARGC_MAX));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_HEAP_PAGE_SIZE"), mrb_fixnum_value(MRB_HEAP_PAGE_SIZE));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_USE_IV_SEGLIST"), mrb_bool_value(DEF_MRB_USE_IV_SEGLIST));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_IVHASH_INIT_SIZE"), mrb_fixnum_value(MRB_IVHASH_INIT_SIZE));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_GC_TURN_OFF_GENERATIONAL"), mrb_bool_value(DEF_MRB_GC_TURN_OFF_GENERATIONAL));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "KHASH_DEFAULT_SIZE"), mrb_fixnum_value(KHASH_DEFAULT_SIZE));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "POOL_ALIGNMENT"), mrb_fixnum_value(POOL_ALIGNMENT));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "POOL_PAGE_SIZE"), mrb_fixnum_value(POOL_PAGE_SIZE));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_STR_BUF_MIN_SIZE"), mrb_fixnum_value(MRB_STR_BUF_MIN_SIZE));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_GC_ARENA_SIZE"), mrb_fixnum_value(MRB_GC_ARENA_SIZE));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "MRB_GC_FIXED_ARENA"), mrb_bool_value(DEF_MRB_GC_FIXED_ARENA));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "ENABLE_STDIO"), mrb_bool_value(DEF_ENABLE_STDIO));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "DISABLE_STDIO"), mrb_bool_value(DEF_DISABLE_STDIO));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "ENABLE_DEBUG"), mrb_bool_value(DEF_ENABLE_DEBUG));
  mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, "DISABLE_DEBUG"), mrb_bool_value(DEF_DISABLE_DEBUG));
  return h;
}

static void
mrb_nofree(mrb_state *mrb, void *p)
{
}

static const struct mrb_data_type mrb_gc_type = { "MrbGC", mrb_nofree };

static mrb_value
mrb_class_s_gc(mrb_state *mrb, mrb_value klass)
{
  struct RClass *mrb_gc_class = mrb_class_get_under(mrb, mrb_class_ptr(klass), "MrbGC");

  return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_gc_class, &mrb_gc_type, &mrb->gc));
}

static mrb_value
mrb_gc_live(mrb_state *mrb, mrb_value self)
{
  struct mrb_gc *gc = DATA_GET_PTR(mrb, self, &mrb_gc_type, struct mrb_gc);
  return mrb_fixnum_value((mrb_int)gc->live);
}

static mrb_value
mrb_gc_live_after_mark(mrb_state *mrb, mrb_value self)
{
  struct mrb_gc *gc = DATA_GET_PTR(mrb, self, &mrb_gc_type, struct mrb_gc);
  return mrb_fixnum_value((mrb_int)gc->live_after_mark);
}

static mrb_value
mrb_gc_threshold(mrb_state *mrb, mrb_value self)
{
  struct mrb_gc *gc = DATA_GET_PTR(mrb, self, &mrb_gc_type, struct mrb_gc);
  return mrb_fixnum_value((mrb_int)gc->threshold);
}

static mrb_value
mrb_gc_interval_ratio(mrb_state *mrb, mrb_value self)
{
  struct mrb_gc *gc = DATA_GET_PTR(mrb, self, &mrb_gc_type, struct mrb_gc);
  return mrb_fixnum_value((mrb_int)gc->interval_ratio);
}

static mrb_value
mrb_gc_step_ratio(mrb_state *mrb, mrb_value self)
{
  struct mrb_gc *gc = DATA_GET_PTR(mrb, self, &mrb_gc_type, struct mrb_gc);
  return mrb_fixnum_value((mrb_int)gc->step_ratio);
}

static mrb_value
mrb_gc_majorgc_old_threshold(mrb_state *mrb, mrb_value self)
{
  struct mrb_gc *gc = DATA_GET_PTR(mrb, self, &mrb_gc_type, struct mrb_gc);
  return mrb_fixnum_value((mrb_int)gc->majorgc_old_threshold);
}

static mrb_value
mrb_class_s_symidx(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value((mrb_int)mrb->symidx);
}

static mrb_value
mrb_class_s_size(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value((mrb_int)sizeof(mrb_state));
}

static mrb_value
mrb_value_class_s_size(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value((mrb_int)sizeof(mrb_value));
}

static mrb_value
mrb_value_class_i(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  return mrb_fixnum_value(mrb_fixnum(obj));
}

static mrb_value
mrb_value_class_f(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  return mrb_float_value(mrb, mrb_float(obj));
}

static const struct mrb_data_type mrb_context_type = { "MrbContext", mrb_nofree };
static const struct mrb_data_type mrb_callinfo_type = { "MrbCallinfo", mrb_nofree };

static mrb_value
mrb_class_s_root_context(mrb_state *mrb, mrb_value klass)
{
  struct mrb_context *root_c = mrb->root_c;
  struct RClass *mrb_context_class = mrb_class_get_under(mrb, mrb_class_ptr(klass), "MrbContext");

  return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_context_class, &mrb_context_type, root_c));
}

static mrb_value
mrb_class_s_current_context(mrb_state *mrb, mrb_value klass)
{
  struct mrb_context *c = mrb->c;
  struct RClass *mrb_context_class = mrb_class_get_under(mrb, mrb_class_ptr(klass), "MrbContext");

  return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_context_class, &mrb_context_type, c));
}

static mrb_value
mrb_context_class_s_size(mrb_state *mrb, mrb_value klass)
{
  return mrb_fixnum_value((mrb_int)sizeof(struct mrb_context));
}

static mrb_value
mrb_context_class_prev(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  struct RClass *mrb_context_class = mrb_class(mrb, self);

  return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_context_class, &mrb_context_type, c->prev));
}

static mrb_value
mrb_context_class_stack_at(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  mrb_int at;

  mrb_get_args(mrb, "i", &at);
  return c->stack[at];
}

static mrb_value
mrb_context_class_stack_index(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  return mrb_fixnum_value((mrb_int)(c->stack - c->stbase));
}

static mrb_value
mrb_context_class_stbase(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  return *c->stbase;
}

static mrb_value
mrb_context_class_stend(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  return *c->stend;
}

static mrb_value
mrb_context_class_ci(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  mrb_callinfo *ci = c->ci;
  struct RClass *mrb_callinfo_class = mrb_class_get_under(mrb, mrb_class(mrb, self), "MrbCallinfo");

  return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_callinfo_class, &mrb_callinfo_type, ci - 1)); /* back by self call */
}

static mrb_value
mrb_context_class_cibase(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  struct RClass *mrb_callinfo_class = mrb_class_get_under(mrb, mrb_class(mrb, self), "MrbCallinfo");

  return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_callinfo_class, &mrb_callinfo_type, c->cibase));
}

static mrb_value
mrb_context_class_ciend(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  struct RClass *mrb_callinfo_class = mrb_class_get_under(mrb, mrb_class(mrb, self), "MrbCallinfo");

  return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_callinfo_class, &mrb_callinfo_type, c->ciend));
}

static mrb_value
mrb_context_class_rescue(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  mrb_value a = mrb_ary_new(mrb);
  mrb_int i;

  for (i = 0; i < c->rsize; i++) {
    if (c->rescue[i])
      mrb_ary_set(mrb, a, i, mrb_fixnum_value((mrb_int)c->rescue[i])); /* FIXME hex str is more good? */
    else
      break;
  }
  return a;
}

static mrb_value
mrb_context_class_rsize(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  return mrb_fixnum_value((mrb_int)c->rsize);
}

static mrb_value
mrb_context_class_ensure(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  mrb_value a = mrb_ary_new(mrb);
  mrb_int i;

  for (i = 0; i < c->esize; i++) {
    if (c->ensure[i])
      mrb_ary_set(mrb, a, i, mrb_obj_value(c->ensure[i]));
    else
      break;
  }
  return a;
}

static mrb_value
mrb_context_class_esize(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  return mrb_fixnum_value((mrb_int)c->esize);
}

static mrb_value
mrb_context_class_status(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  return mrb_str_new_cstr(mrb, fiber_state2str(c->status));
}

static mrb_value
mrb_context_class_fib(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  return mrb_obj_value(c->fib);
}

static mrb_value
mrb_context_class_stack_length(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c;

  c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  return mrb_fixnum_value((mrb_int)(c->stend - c->stbase));
}

static mrb_value
mrb_context_class_ci_length(mrb_state *mrb, mrb_value self)
{
  struct mrb_context *c;

  c = DATA_GET_PTR(mrb, self, &mrb_context_type, struct mrb_context);
  return mrb_fixnum_value((mrb_int)(c->ciend - c->cibase));
}

static mrb_value
mrb_callinfo_class_mid(mrb_state *mrb, mrb_value self)
{
  mrb_callinfo *ci = DATA_GET_PTR(mrb, self, &mrb_callinfo_type, mrb_callinfo);
  return mrb_symbol_value(ci->mid);
}

static mrb_value
mrb_callinfo_class_proc(mrb_state *mrb, mrb_value self)
{
  mrb_callinfo *ci = DATA_GET_PTR(mrb, self, &mrb_callinfo_type, mrb_callinfo);
  return mrb_obj_value(ci->proc);
}

static mrb_value
mrb_callinfo_class_stackent(mrb_state *mrb, mrb_value self)
{
  mrb_callinfo *ci = DATA_GET_PTR(mrb, self, &mrb_callinfo_type, mrb_callinfo);
  return *ci->stackent;
}

static mrb_value
mrb_callinfo_class_nregs(mrb_state *mrb, mrb_value self)
{
  mrb_callinfo *ci = DATA_GET_PTR(mrb, self, &mrb_callinfo_type, mrb_callinfo);
  return mrb_fixnum_value((mrb_int)ci->stackent);
}

static mrb_value
mrb_callinfo_class_ridx(mrb_state *mrb, mrb_value self)
{
  mrb_callinfo *ci = DATA_GET_PTR(mrb, self, &mrb_callinfo_type, mrb_callinfo);
  return mrb_fixnum_value(ci->ridx);
}

static mrb_value
mrb_callinfo_class_epos(mrb_state *mrb, mrb_value self)
{
  mrb_callinfo *ci = DATA_GET_PTR(mrb, self, &mrb_callinfo_type, mrb_callinfo);
#if MRUBY_RELEASE_NO >= 10300
  return mrb_fixnum_value(ci->epos);
#else
  return mrb_fixnum_value(ci->eidx);
#endif
}

static mrb_value
rbasic_s_ttlist(mrb_state *mrb, mrb_value klass)
{
  mrb_value h = mrb_hash_new(mrb);
  struct vtypes *vs;

  for (vs = vtypelist; vs->name; vs++) {
    mrb_hash_set(mrb, h, mrb_str_new_cstr(mrb, vs->name), mrb_fixnum_value((mrb_int)vs->tt));
  }
  return h;
}

static mrb_value
rbasic_s_size(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value((mrb_int)sizeof(struct RBasic));
}

static mrb_value
rbasic_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;

  mrb_get_args(mrb, "o", &obj);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@obj"), obj);
  return self;
}

static mrb_value
rbasic_tt(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  enum mrb_vtype tt = mrb_type(obj);

  return mrb_str_new_cstr(mrb, tt2str(tt));
}

static mrb_value
rbasic_color(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  uint32_t color = mrb_obj_ptr(obj)->color;

  return mrb_str_new_cstr(mrb, color2str(color));
}

static mrb_value
rbasic_flags(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));

  return mrb_fixnum_value((mrb_int)mrb_obj_ptr(obj)->flags);
}

static mrb_value
rclass_s_size(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value((mrb_int)sizeof(struct RClass));
}

static mrb_value
rclass_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;

  mrb_get_args(mrb, "C", &obj);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@obj"), obj);
  return self;
}

static mrb_value
rclass_super(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  return mrb_obj_value(mrb_class_ptr(obj)->super);
}

static mrb_value
rclass_singleton_class_p(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  return mrb_bool_value(mrb_class_ptr(obj)->tt == MRB_TT_SCLASS);
}

static mrb_value
rstring_s_size(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value((mrb_int)sizeof(struct RString));
}

static mrb_value
rstring_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;

  mrb_get_args(mrb, "S", &obj);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@obj"), obj);
  return self;
}

static mrb_value
rstring_embed_p(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));

  return mrb_bool_value((RSTRING(obj)->flags & MRB_STR_EMBED) == MRB_STR_EMBED);
}

static mrb_value
rstring_nofree_p(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));

  return mrb_bool_value((RSTRING(obj)->flags & MRB_STR_NOFREE) == MRB_STR_NOFREE);
}

static mrb_value
rstring_shared_p(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));

  return mrb_bool_value((RSTRING(obj)->flags & MRB_STR_SHARED) == MRB_STR_SHARED);
}

static mrb_value
rstring_capa(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));

  return mrb_fixnum_value(RSTRING_CAPA(obj));
}

static mrb_value
rproc_s_size(mrb_state *mrb, mrb_value mod)
{
  return mrb_fixnum_value((mrb_int)sizeof(struct RProc));
}

static mrb_value
rproc_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_nil_value(), block;

  mrb_get_args(mrb, "|o&", &obj, &block);
  if (mrb_type(block) == MRB_TT_PROC) {
    if (mrb_nil_p(obj)) {
      obj = block;
    }
    else {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "RProc can set only one Proc/Block");
    }
  }
  if (mrb_type(obj) != MRB_TT_PROC)
    mrb_raisef(mrb, E_TYPE_ERROR, "RProc can not set %S (expected Proc)", obj);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@obj"), obj);
  return self;
}

static mrb_value
rproc_cfunc_p(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));

  return mrb_bool_value(MRB_PROC_CFUNC_P(mrb_proc_ptr(obj)));
}

static mrb_value
rproc_strict_p(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));

  return mrb_bool_value(MRB_PROC_STRICT_P(mrb_proc_ptr(obj)));
}

static mrb_value
rproc_target_class(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));

#ifdef MRB_PROC_TARGET_CLASS
  return mrb_obj_value(MRB_PROC_TARGET_CLASS(mrb_proc_ptr(obj)));
#else
  return mrb_obj_value(mrb_proc_ptr(obj)->target_class);
#endif
}

static mrb_value
rproc_irep(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  struct RClass *irep_class = mrb_class_get_under(mrb, mrb_obj_class(mrb, self), "MrbIrep");

  return mrb_funcall(mrb, mrb_obj_value(irep_class), "new", 1, obj);
}

static mrb_value
mrb_irep_class_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value obj, block;
  mrb_int argc;

  argc = mrb_get_args(mrb, "|o&", &obj, &block);
  if (argc == 2) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "MrbIrep can set only one object");
  }
  if (!mrb_nil_p(block)) {
    obj = block;
  }
  if (mrb_type(obj) != MRB_TT_PROC)
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "MrbIrep can not set %S", obj);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@obj"), obj);
  return self;
}

static mrb_value
mrb_irep_class_nlocals(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));

  return mrb_fixnum_value((mrb_int)mrb_proc_ptr(obj)->body.irep->nlocals);
}

static mrb_value
mrb_irep_class_nregs(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));

  return mrb_fixnum_value((mrb_int)mrb_proc_ptr(obj)->body.irep->nregs);
}

static mrb_value
mrb_irep_class_flags(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));

  return mrb_fixnum_value((mrb_int)mrb_proc_ptr(obj)->body.irep->flags);
}

static mrb_value
mrb_irep_class_iseq(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;
  mrb_value a = mrb_ary_new_capa(mrb, (mrb_int)irep->ilen);
  mrb_int i;

  for (i = 0; i < irep->ilen; i++) {
    mrb_ary_set(mrb, a, i, mrb_fixnum_value((mrb_int)irep->iseq[i]));
  }
  return a;
}

static mrb_value
mrb_irep_class_pool(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_ary_new_from_values(mrb, (mrb_int)irep->plen, irep->pool);
}

static mrb_value
mrb_irep_class_syms(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;
  mrb_value a = mrb_ary_new_capa(mrb, (mrb_int)irep->slen);
  mrb_int i;

  for (i = 0; i < irep->slen; i++) {
    mrb_ary_set(mrb, a, i, mrb_symbol_value(irep->syms[i]));
  }
  return a;
}

static mrb_value
mrb_irep_class_reps(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;
  mrb_value a = mrb_ary_new_capa(mrb, (mrb_int)irep->slen);
  struct RClass *irep_class = mrb_obj_class(mrb, self);
  mrb_int i;

  for (i = 0; i < irep->rlen; i++) {
    struct RProc *proc = mrb_proc_new(mrb, irep->reps[i]);
    mrb_value new_irep = mrb_funcall(mrb, mrb_obj_value(irep_class), "new", 1, mrb_obj_value(proc));
    mrb_ary_set(mrb, a, i, new_irep);
  }
  return a;
}

static mrb_value
mrb_irep_class_lv(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;
  mrb_value a = mrb_ary_new_capa(mrb, (mrb_int)(irep->nlocals - 1));
  mrb_int i;

  if (!irep->lv)
    return mrb_ary_new(mrb);

  for (i = 0; i < irep->nlocals - 1; ++i) {
    if (irep->lv[i].name) {
      mrb_value h = mrb_hash_new(mrb);
      mrb_hash_set(mrb, h, mrb_check_intern_cstr(mrb, "name"), mrb_symbol_value(irep->lv[i].name));
      mrb_hash_set(mrb, h, mrb_check_intern_cstr(mrb, "r"), mrb_fixnum_value((mrb_int)irep->lv[i].r));
      mrb_ary_set(mrb, a, i, h);
    }
  }
  return a;
}

static mrb_value
mrb_irep_class_filename(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_str_new_cstr(mrb, irep->filename);
}

static mrb_value
mrb_irep_class_lines(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;
  mrb_int iseq_no;
  mrb_value a = mrb_ary_new_capa(mrb, (mrb_int)irep->ilen);

  if (!irep->lines)
    return a;
  for (iseq_no = 0; iseq_no < irep->ilen; iseq_no++) {
    mrb_ary_set(mrb, a, iseq_no, mrb_fixnum_value((mrb_int)irep->lines[iseq_no]));
  }
  return a;
}

static mrb_value
mrb_irep_class_ilen(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_fixnum_value((mrb_int)irep->ilen);
}

static mrb_value
mrb_irep_class_plen(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_fixnum_value((mrb_int)irep->plen);
}

static mrb_value
mrb_irep_class_slen(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_fixnum_value((mrb_int)irep->slen);
}

static mrb_value
mrb_irep_class_rlen(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_fixnum_value((mrb_int)irep->rlen);
}

static mrb_value
mrb_irep_class_refcnt(mrb_state *mrb, mrb_value self)
{
  mrb_value obj = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@obj"));
  mrb_irep *irep = mrb_proc_ptr(obj)->body.irep;

  return mrb_fixnum_value((mrb_int)irep->refcnt);
}

static mrb_value
renv_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value obj, block;
  mrb_int argc;

  argc = mrb_get_args(mrb, "|o&", &obj, &block);
  if (argc == 2) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "REnv can set only one object");
  }
  if (!mrb_nil_p(block)) {
    obj = block;
  }
  if (mrb_type(obj) != MRB_TT_PROC)
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "REnv can not set %S", obj);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@obj"), obj);
  return self;
}

void
mrb_mruby_research_gem_init(mrb_state* mrb)
{
  struct RClass *mrb_class = mrb_define_module(mrb, "MrbState");
  struct RClass *mrb_gc_class = mrb_define_class_under(mrb, mrb_class, "MrbGC", mrb->object_class);
  struct RClass *mrb_value_class = mrb_define_class_under(mrb, mrb_class, "MrbValue", mrb->object_class);
  struct RClass *mrb_context_class = mrb_define_class_under(mrb, mrb_class, "MrbContext", mrb->object_class);
  struct RClass *mrb_callinfo_class = mrb_define_class_under(mrb, mrb_context_class, "MrbCallinfo", mrb->object_class);
  struct RClass *rbasic = mrb_define_class_under(mrb, mrb_class, "RBasic", mrb->object_class);
  struct RClass *rclass = mrb_define_class_under(mrb, mrb_class, "RClass", rbasic);
  struct RClass *rstring = mrb_define_class_under(mrb, mrb_class, "RString", rbasic);
  struct RClass *rproc = mrb_define_class_under(mrb, mrb_class, "RProc", rbasic);
  struct RClass *renv = mrb_define_class_under(mrb, mrb_class, "REnv", rbasic);
  struct RClass *mrb_irep_class = mrb_define_class_under(mrb, rproc, "MrbIrep", mrb->object_class);

  MRB_SET_INSTANCE_TT(mrb_context_class, MRB_TT_DATA);
  MRB_SET_INSTANCE_TT(mrb_callinfo_class, MRB_TT_DATA);

  mrb_define_const(mrb, mrb_class, "MRB_INT_BIT", mrb_fixnum_value(MRB_INT_BIT));
  mrb_define_const(mrb, mrb_class, "MRB_INT_MIN", mrb_fixnum_value(MRB_INT_MIN));
  mrb_define_const(mrb, mrb_class, "MRB_INT_MAX", mrb_fixnum_value(MRB_INT_MAX));
  mrb_define_class_method(mrb, mrb_class, "mrbconf", mrb_class_s_mrbconf, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_class, "symidx", mrb_class_s_symidx, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_class, "size", mrb_class_s_size, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_class, "root_c", mrb_class_s_root_context, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_class, "c", mrb_class_s_current_context, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mrb_class, "gc", mrb_class_s_gc, MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb_gc_class, "live", mrb_gc_live, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gc_class, "live_after_mark", mrb_gc_live_after_mark, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gc_class, "threshold", mrb_gc_threshold, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gc_class, "interval_ratio", mrb_gc_interval_ratio, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gc_class, "step_ratio", mrb_gc_step_ratio, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_gc_class, "majorgc_old_threshold", mrb_gc_majorgc_old_threshold, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, mrb_value_class, "size", mrb_value_class_s_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_value_class, "initialize", rbasic_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_value_class, "i", mrb_value_class_i, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_value_class, "f", mrb_value_class_f, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, mrb_context_class, "size", mrb_context_class_s_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "prev", mrb_context_class_prev, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "stack_at", mrb_context_class_stack_at, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_context_class, "stack_index", mrb_context_class_stack_index, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "stbase", mrb_context_class_stbase, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "stend", mrb_context_class_stend, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "ci", mrb_context_class_ci, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "cibase", mrb_context_class_cibase, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "ciend", mrb_context_class_ciend, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "rescue", mrb_context_class_rescue, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "rsize", mrb_context_class_rsize, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "ensure", mrb_context_class_ensure, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "esize", mrb_context_class_esize, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "status", mrb_context_class_status, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "fib", mrb_context_class_fib, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "stack_length", mrb_context_class_stack_length, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_context_class, "ci_length", mrb_context_class_ci_length, MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb_callinfo_class, "mid", mrb_callinfo_class_mid, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_callinfo_class, "proc", mrb_callinfo_class_proc, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_callinfo_class, "stackent", mrb_callinfo_class_stackent, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_callinfo_class, "nregs", mrb_callinfo_class_nregs, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_callinfo_class, "ridx", mrb_callinfo_class_ridx, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_callinfo_class, "eidx", mrb_callinfo_class_epos, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_callinfo_class, "epos", mrb_callinfo_class_epos, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, rbasic, "ttlist", rbasic_s_ttlist, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, rbasic, "size", rbasic_s_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, rbasic, "initialize", rbasic_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rbasic, "tt", rbasic_tt, MRB_ARGS_NONE());
  mrb_define_method(mrb, rbasic, "color", rbasic_color, MRB_ARGS_NONE());
  mrb_define_method(mrb, rbasic, "flags", rbasic_flags, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, rclass, "size", rclass_s_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "initialize", rclass_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rclass, "super", rclass_super, MRB_ARGS_NONE());
  mrb_define_method(mrb, rclass, "singleton_class?", rclass_singleton_class_p, MRB_ARGS_NONE());

  mrb_define_const(mrb, rstring, "RSTRING_EMBED_LEN_MAX", mrb_fixnum_value(RSTRING_EMBED_LEN_MAX));
  mrb_define_class_method(mrb, rstring, "size", rstring_s_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, rstring, "initialize", rstring_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, rstring, "shared?", rstring_shared_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, rstring, "nofree?", rstring_nofree_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, rstring, "embed?", rstring_embed_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, rstring, "capa", rstring_capa, MRB_ARGS_NONE());

#ifdef MRB_PROC_CFUNC_FL
  mrb_define_const(mrb, rproc, "MRB_PROC_CFUNC", mrb_fixnum_value(MRB_PROC_CFUNC_FL));
#else
  mrb_define_const(mrb, rproc, "MRB_PROC_CFUNC", mrb_fixnum_value(MRB_PROC_CFUNC));
#endif
  mrb_define_const(mrb, rproc, "MRB_PROC_STRICT", mrb_fixnum_value(MRB_PROC_STRICT));
  mrb_define_class_method(mrb, rproc, "size", rproc_s_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, rproc, "initialize", rproc_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, rproc, "cfunc?", rproc_cfunc_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, rproc, "strict?", rproc_strict_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, rproc, "target_class", rproc_target_class, MRB_ARGS_NONE());
  mrb_define_method(mrb, rproc, "irep", rproc_irep, MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb_irep_class, "initialize", mrb_irep_class_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_irep_class, "nlocals", mrb_irep_class_nlocals, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "nregs", mrb_irep_class_nregs, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "flags", mrb_irep_class_flags, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "iseq", mrb_irep_class_iseq, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "pool", mrb_irep_class_pool, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "syms", mrb_irep_class_syms, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "reps", mrb_irep_class_reps, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "lv", mrb_irep_class_lv, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "filename", mrb_irep_class_filename, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "lines", mrb_irep_class_lines, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "ilen", mrb_irep_class_ilen, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "plen", mrb_irep_class_plen, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "slen", mrb_irep_class_slen, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "rlen", mrb_irep_class_rlen, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_irep_class, "refcnt", mrb_irep_class_refcnt, MRB_ARGS_NONE());

  mrb_define_method(mrb, renv, "initialize", renv_initialize, MRB_ARGS_REQ(1));
}

void
mrb_mruby_research_gem_final(mrb_state* mrb) {
}
