class Object
  def to_RBasic
    Mruby::RBasic.new(self)
  end

  def to_RClass
    Mruby::RClass.new(self)
  end

  def to_RString
    Mruby::RString.new(self)
  end
end
