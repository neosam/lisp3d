function initText(id)

	r, g, b = quadGetRGB(id)
	print ("Farben", r, g, b)
	b = 1
	print ("Farben neu", r, g, b);
	quadSetRGB(id, r, g, b)
  
end
