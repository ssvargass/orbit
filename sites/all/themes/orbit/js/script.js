(function ($) {
  $(document).ready(function(){
    $('#og-wall-form .ob_text').addClass('active');
  })
	Drupal.behaviors.orbit = {
    attach: function (context, settings) {
      $('#og-wall-form').once('wall_form',function(){
        var form = $(this);
        $('label').click(function(){
          $('.active', form).removeClass('active');
          $(this).parents('.s_add_file').addClass('active');
        })
      });
    }
  };
})(jQuery);