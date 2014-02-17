(function ($) {
  $(document).ready(function(){
    $('#og-wall-form .form-type-textarea').addClass('active');
  })
	Drupal.behaviors.orbit = {
    attach: function (context, settings) {
      $('#og-wall-form').once('wall_form',function(){
        var form = $(this);
        $('label').click(function(){
          $('.active', form).removeClass('active');
          var padre = $(this).parent();
          if(padre.hasClass('form-type-textarea')) padre.addClass('active');
          if(padre.hasClass('form-type-managed-file')) padre.parent().addClass('active');
        })
      });
    }
  };
})(jQuery);