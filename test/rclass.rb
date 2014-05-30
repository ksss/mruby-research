assert 'MrbState::RClass.new' do
  r = MrbState::RClass.new(Class.new)
  assert_equal MrbState::RClass, r.class
  assert_equal MrbState::RBasic, r.class.superclass
  assert_equal "MRB_TT_CLASS", r.tt
end

assert 'Object#to_RClass' do
  r = Class.new.to_RClass
  assert_equal MrbState::RClass, r.class
  assert_equal MrbState::RBasic, r.class.superclass
  assert_raise(ArgumentError){ [].to_RClass }
end

assert 'MrbState::RClass#super' do
  r = Class.new.to_RClass
  assert_equal Object, r.super
end
