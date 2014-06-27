assert 'MrbState::RProc.new' do
  r = MrbState::RProc.new do
    "this is proc"
  end
  assert_equal MrbState::RProc, r.class
  assert_equal MrbState::RBasic, r.class.superclass
  assert_equal "MRB_TT_PROC", r.tt
  assert_raise(ArgumentError){ MrbState::RProc.new(Proc.new{}){} }
  assert_raise(TypeError){ MrbState::RProc.new(1) }
end

assert 'Object#to_RProc' do
  r = ->{}.to_RProc
  assert_equal MrbState::RProc, r.class
  assert_equal MrbState::RBasic, r.class.superclass
end

assert 'MrbState::RProc.size' do
  assert_true 0 < MrbState::RProc.size
end

assert 'MrbState::RProc#cfunc?' do
  r = ->{}.to_RProc
  assert_false r.cfunc?
  # assert_true ? # do you have idea?
end

assert 'MrbState::RProc#strict?' do
  assert_true ->{}.to_RProc.strict?
  assert_false Proc.new{}.to_RProc.strict?
end

assert 'MrbState::RProc#target_class' do
  assert_equal Object, ->{}.to_RProc.target_class
end

assert 'MrbState::RProc#irep' do
  assert_kind_of MrbState::RProc::MrbIrep, ->{}.to_RProc.irep
end
