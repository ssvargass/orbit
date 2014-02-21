(function ($) {
  var personal = new Array();
  $(document).ready(function(){
    $.fn.ob_wall_directory = function(options) {
      $.colorbox(options);
    }; 
    $('.ob-profile a').click(function(e){
      
      e.preventDefault();
      return false;
    })
  })
  $(function(){       
    $('body').ajaxStop(function() {

    	if(personal.length > 0) {
    		for (key in personal) {
    			$('#colorbox .views-field-uid').each(function(){
    				if($('.field-content', this).html() == personal[key]) $(this).parent().addClass('active');
    			})	
    		}
    	}

    	$('.views-field-uid','#colorbox .view-directorio').click(function(){
    		var padre = $(this).parent();
    		var uid = $('.field-content',this).html();
    		if(!padre.hasClass('active')){
	    		padre.addClass('active');
	    		personal.push(uid);
    		} else {
    			padre.removeClass('active');
    			removeFromArray(personal, uid);
    		}
    	})
    	$('#colorbox .s_submit').click(function(){
    		persons = 'specific=' + personal.join();
    		$.colorbox.close();
    		$('#og-wall-form .s_specific').val(persons);
    	})
    });
   });
})(jQuery);


 function removeFromArray(array, item){
    while((index = array.indexOf(item)) > -1)
          array.splice(index,1); 
 }