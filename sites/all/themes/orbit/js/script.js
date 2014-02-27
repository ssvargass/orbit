(function ($) {
  $(document).ready(function(){
    $('#og-wall-form .ob_text').addClass('active');
    $('.views-exposed-form .views-widget-filter-combine').hide_label();
    $('#block-ob-wall-ob-profile .ob-close').click(function(e){
        up = undefined;
        if($(this).parents('#block-ob-wall-ob-profile').hasClass('actice')){
          altura = '0em';
        } else {
          altura = '18.5em'
          up = 'true';
        }
        $('#block-ob-wall-ob-profile').animate({height:altura},500, function(){
          if(up) {
            $(this).addClass('actice')
          } else {
            $(this).removeClass('actice')
          }
        })
        e.preventDefault();
        return false;
      })
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
    }
  };
})(jQuery);