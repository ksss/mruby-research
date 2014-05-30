assert 'Mrb::RBasic.new' do
  r = Mrb::RBasic.new(Object.new)
  assert_equal Mrb::RBasic, r.class
  assert_equal Object, r.class.superclass
end

assert 'Object#to_RBasic' do
  r = [1,2,3].to_RBasic
  assert_equal Mrb::RBasic, r.class
  assert_equal Object, r.class.superclass
end

assert 'Mrb::RBasic.ttlist' do
  assert_true Mrb::RBasic.ttlist.has_key?("MRB_TT_ARRAY")
end

assert 'Mrb::RBasic#tt' do
  r = [1,2,3].to_RBasic
  assert_equal "MRB_TT_ARRAY", r.tt

  r = 1.to_RBasic
  assert_equal "MRB_TT_FIXNUM", r.tt
end

assert 'Mrb::RBasic#color' do
  r = [1,2,3].to_RBasic
  gc_definition = ["MRB_GC_GRAY","MRB_GC_WHITE_A","MRB_GC_WHITE_B","MRB_GC_WHITES","MRB_GC_BLACK"]
  assert_include gc_definition, r.color
end

assert 'Mrb::RBasic#flags' do
  r = [1,2,3].to_RBasic
  assert_kind_of Fixnum, r.flags
end

