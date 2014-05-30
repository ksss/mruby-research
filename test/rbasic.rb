assert 'Mruby::RBasic.new' do
  r = Mruby::RBasic.new(Object.new)
  assert_equal Mruby::RBasic, r.class
  assert_equal Object, r.class.superclass
end

assert 'Object#to_RBasic' do
  r = [1,2,3].to_RBasic
  assert_equal Mruby::RBasic, r.class
  assert_equal Object, r.class.superclass
end

assert 'Mruby::RBasic.ttlist' do
  assert_true Mruby::RBasic.ttlist.has_key?("MRB_TT_ARRAY")
end

assert 'Mruby::RBasic#tt' do
  r = [1,2,3].to_RBasic
  assert_equal "MRB_TT_ARRAY", r.tt

  r = 1.to_RBasic
  assert_equal "MRB_TT_FIXNUM", r.tt
end

assert 'Mruby::RBasic#color' do
  r = [1,2,3].to_RBasic
  gc_definition = ["MRB_GC_GRAY","MRB_GC_WHITE_A","MRB_GC_WHITE_B","MRB_GC_WHITES","MRB_GC_BLACK"]
  assert_include gc_definition, r.color
end

assert 'Mruby::RBasic#flags' do
  r = [1,2,3].to_RBasic
  assert_kind_of Fixnum, r.flags
end

