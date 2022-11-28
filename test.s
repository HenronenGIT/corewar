




   .name		"
   
   
   # is this saved?
   
   
   
   test_name"
	
	  .comment    "This is a comment?

	  #saved ?
	  



	  still saved?
	  "	
		
live	%1
l2:	
sti	r1,%:live,%0
	and	r1,%0,r1

	and	r1,%0,r1
	lldi 42, r2, r3 # testing T_IND
	st r1, :l2 # testing T_IND

live:	live	%1
	zjmp	%:live
