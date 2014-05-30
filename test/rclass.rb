assert 'Mrb::RClass.new' do
  r = Mrb::RClass.new(Class.new)
  assert_equal Mrb::RClass, r.class
  assert_equal Mrb::RBasic, r.class.superclass
  assert_equal "MRB_TT_CLASS", r.tt
end

assert 'Object#to_RClass' do
  r = Class.new.to_RClass
  assert_equal Mrb::RClass, r.class
  assert_equal Mrb::RBasic, r.class.superclass
  assert_raise(ArgumentError){ [].to_RClass }
end

assert 'Mrb::RClass#super' do
  r = Class.new.to_RClass
  assert_equal Object, r.super
end
