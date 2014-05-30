assert 'Mruby::RClass.new' do
  r = Mruby::RClass.new(Class.new)
  assert_equal Mruby::RClass, r.class
  assert_equal Mruby::RBasic, r.class.superclass
  assert_equal "MRB_TT_CLASS", r.tt
end

assert 'Object#to_RClass' do
  r = Class.new.to_RClass
  assert_equal Mruby::RClass, r.class
  assert_equal Mruby::RBasic, r.class.superclass
  assert_raise(ArgumentError){ [].to_RClass }
end

assert 'Mruby::RClass#super' do
  r = Class.new.to_RClass
  assert_equal Object, r.super
end
