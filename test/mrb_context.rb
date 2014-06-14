assert 'MrbState::MrbContext.new' do
  context = MrbState::MrbContext.new

  assert_equal MrbState::MrbContext, context.class
  assert_equal "MRB_TT_DATA", context.to_RBasic.tt
end

assert 'MrbState::MrbContext.root_c' do
  root_c = MrbState::MrbContext.root_c

  assert_equal MrbState::MrbContext, root_c.class
end

assert 'MrbState::MrbContext.c' do
  c = MrbState::MrbContext.c

  assert_equal MrbState::MrbContext, c.class
end

assert 'MrbState.stack_length' do
  assert_true 0 < MrbState::MrbContext.stack_length
end

assert 'MrbState.ci_length' do
  assert_true 0 < MrbState::MrbContext.ci_length
end

assert 'MrbState::MrbContext#stack_length' do
  assert_true 0 < MrbState::MrbContext.new.stack_length
end

assert 'MrbState::MrbContext#ci_length' do
  assert_true 0 < MrbState::MrbContext.new.ci_length
end

assert 'MrbState::MrbContext#==' do
  c1 = MrbState::MrbContext.new
  c2 = MrbState::MrbContext.new
  assert_include [true, false], c1 == c2
  assert_true c1 == c2
end
