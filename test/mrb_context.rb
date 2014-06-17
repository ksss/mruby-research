assert 'MrbState.root_c' do
  assert_kind_of MrbState::MrbContext, MrbState.root_c
end

assert 'MrbState.c' do
  assert_kind_of MrbState::MrbContext, MrbState.c
end

assert 'MrbState::MrbContext#stbase' do
  assert_equal self, MrbState.root_c.stbase
end

assert 'MrbState::MrbContext#stend' do
  assert_nil MrbState.root_c.stend
end

assert 'MrbState::MrbContext#stack_at' do
  root_c = MrbState.root_c
  assert_equal root_c, root_c.stack_at(0)
end

assert 'MrbState::MrbContext#ci_length' do
  assert_true 0 < MrbState.root_c.ci_length
end

assert 'MrbState::MrbContext#stack_length' do
  assert_true 0 < MrbState.root_c.stack_length
end

assert 'MrbState::MrbContext#status' do
  assert_equal "MRB_FIBER_RUNNING", MrbState.root_c.status
end
