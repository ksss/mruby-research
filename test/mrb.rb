assert 'Mrb.nan_boxing?' do
  assert_include [true,false], Mrb.nan_boxing?
end
