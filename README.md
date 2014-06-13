# mruby-research

research for mruby

## Synopsis

```ruby
#same means in C `sizeof(mrb_state)`
MrbState.size #=> 328

#count of live object for GC
MrbState.live #=> 1575

#show hash of current configuration defined by mrbconf.h
MrbState.mrbconf #=> {"MRB_USE_FLOAT"=>false, "MRB_INT16"=>false, "MRB_INT64"=>false, "MRB_NAN_BOXING"=>false, "MRB_ENDIAN_BIG"=>false, "MRB_WORD_BOXING"=>false, "MRB_FUNCALL_ARGC_MAX"=>16, "MRB_HEAP_PAGE_SIZE"=>1024, "MRB_USE_IV_SEGLIST"=>false, "MRB_IVHASH_INIT_SIZE"=>8, "MRB_GC_TURN_OFF_GENERATIONAL"=>false, "KHASH_DEFAULT_SIZE"=>32, "POOL_ALIGNMENT"=>4, "POOL_PAGE_SIZE"=>1600, "MRB_STR_BUF_MIN_SIZE"=>128, "MRB_GC_ARENA_SIZE"=>100, "MRB_GC_FIXED_ARENA"=>false, "ENABLE_STDIO"=>true, "DISABLE_STDIO"=>false, "ENABLE_DEBUG"=>false, "DISABLE_DEBUG"=>true}

#show object type name in C definition
1.to_RBasic.tt #=> "MRB_TT_FIXNUM"

# check use embed-string?
"foo".to_RString.embed? #=> true
```

## Installation

### use github repository

Write in /mruby/build_config.rb

```ruby
MRuby::Build.new do |conf|
  conf.gem :github => 'ksss/mruby-research', :branch => 'master'
end
```

## License

MIT
