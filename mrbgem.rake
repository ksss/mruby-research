MRuby::Gem::Specification.new('mruby-research') do |spec|
  spec.license = 'MIT'
  spec.author  = 'ksss <co000ri@gmail.com>'
  if File.exist?(File.join(MRUBY_ROOT, 'mrbgems/mruby-metaprog'))
    # for mruby-2.0+
    spec.add_dependency 'mruby-metaprog', core: 'mruby-metaprog'
  end
end
