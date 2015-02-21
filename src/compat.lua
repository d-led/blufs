-- http://www.lua.org/pil/5.1.html
unpack = function (t, i)
  i = i or 1
  if t[i] ~= nil then
    return t[i], unpack(t, i + 1)
  end
end