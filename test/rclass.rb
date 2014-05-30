assert 'MrbRClass.new' do
  r = MrbRClass.new(Class.new)
  assert_equal MrbRClass, r.class
  assert_equal MrbRBasic, r.class.superclass
  assert_equal "MRB_TT_CLASS", r.tt
end

assert 'Object#to_RClass' do
  r = Class.new.to_RClass
  assert_equal MrbRClass, r.class
  assert_equal MrbRBasic, r.class.superclass
  assert_raise(ArgumentError){ [].to_RClass }
end

assert 'MrbRClass#super' do
  r = Class.new.to_RClass
  assert_equal Object, r.super
end
