(function ($) {
  $(document).ready(function(){
    $('#og-wall-form .ob_text').addClass('active');
    $('.views-exposed-form .views-widget-filter-combine').hide_label();
  })
  $.fn.hide_label = function(){
    var complete_input = this;
    if($(complete_input).find('input').length > 0){
      if($(complete_input).find('input').val() != ''){
        $(this).find('label').hide();
      }

      $(complete_input).find('input').focus(function() {
        complete_input.find("label").hide();
      });

      $(complete_input).find('input').blur(function() {
        console.log(this);
        if($(this).val() === ''){
          complete_input.find("label").show();
        }
      });
    }
    if($(complete_input).find('textarea').length > 0){
      if($(complete_input).find('textarea').val() != ''){
        $(this).find('label').hide();
      }

      $(complete_input).find('textarea').focus(function() {
        complete_input.find("label").hide();
      });

      $(complete_input).find('textarea').blur(function() {
        console.log(this);
        if($(this).val() === ''){
          complete_input.find("label").show();
        }
      });
    }
  }
	Drupal.behaviors.orbit = {
    attach: function (context, settings) {
      $('#og-wall-form').once('wall_form',function(){
        var form = $(this);
        $('label').click(function(){
          $('.active', form).removeClass('active');
          $(this).parents('.s_add_file').addClass('active');
        })
      });
      $('.ob-profile:not(.active) .ob-close').click(function(e){
        $('#block-ob-wall-ob-profile').animate({height:'18.5em'},500, function(){
          $(this).addClass(active)
        })
        e.preventDefault();
        return false;
      })

      $('.ob-profile.active .ob-close').click(function(){
        $('#block-ob-wall-ob-profile').animate({height:'0em'},500, function(){
          $(this).removeClass('active')
        })
      })
    }
  };
})(jQuery);