assert 'MrbState::MrbValue' do
  r = MrbState::MrbValue.new(1)
  assert_equal MrbState::MrbValue, r.class
  assert_equal Object, r.class.superclass
end

assert 'Object#to_mrb_value' do
  r = 1.to_mrb_value
  assert_equal MrbState::MrbValue, r.class
  assert_equal Object, r.class.superclass
end

assert 'MrbState::MrbValue#i' do
  r = 123.to_mrb_value
  assert_equal 123, r.i
end

assert 'MrbState::MrbValue#f' do
  r = 1.0.to_mrb_value
  assert_equal 1.0, r.f
end
