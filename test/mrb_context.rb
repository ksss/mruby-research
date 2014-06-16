assert 'MrbState.root_c' do
  assert_kind_of MrbState::MrbContext, MrbState.root_c
end

assert 'MrbState.c' do
  assert_kind_of MrbState::MrbContext, MrbState.c
end

assert 'MrbState::MrbContext#ci_length' do
  assert_true 0 < MrbState.root_c.ci_length
end

assert 'MrbState::MrbContext#stack_length' do
  assert_true 0 < MrbState.root_c.stack_length
end
