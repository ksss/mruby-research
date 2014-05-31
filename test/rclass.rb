assert 'MrbState::RClass.new' do
  r = MrbState::RClass.new(Class.new)
  assert_equal MrbState::RClass, r.class
  assert_equal MrbState::RBasic, r.class.superclass
  assert_equal "MRB_TT_CLASS", r.tt
  assert_raise(ArgumentError){ MrbState::RClass.new(1) }
end

assert 'Object#to_RClass' do
  r = Class.new.to_RClass
  assert_equal MrbState::RClass, r.class
  assert_equal MrbState::RBasic, r.class.superclass
end

assert 'MrbState::RClass.size' do
  assert_true 0 < MrbState::RClass.size
end

assert 'MrbState::RClass#super' do
  r = Class.new.to_RClass
  assert_equal Object, r.super
end
