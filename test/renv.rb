assert 'MrbState::REnv.new' do
  r = MrbState::REnv.new(->{})
  assert_equal MrbState::REnv, r.class
  assert_equal MrbState::RBasic, r.class.superclass
  assert_equal "MRB_TT_PROC", r.tt
  assert_raise(ArgumentError){ MrbState::REnv.new(1) }
end

assert 'Object#to_REnv' do
  r = ->{}.to_REnv
  assert_equal MrbState::REnv, r.class
  assert_equal MrbState::RBasic, r.class.superclass
end

