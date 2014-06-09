assert 'MrbState.stack_length' do
  assert_true 0 < MrbState::MrbContext.stack_length
end

assert 'MrbState.ci_length' do
  assert_true 0 < MrbState::MrbContext.ci_length
end
