(function ($) {
  $(document).ready(function(){
    $.fn.ob_room_reload = function(options) {
      console.log('eleimina');
      window.parent.location.reload();
      location.reload(true);
    };
    galscrollMouse();
    function galscrollMouse(){
        gallencierra = $('.view-colaboradores');
        nulistado = $('.view-colaboradores .views-row').length;
        var ciclos = Math.round(nulistado/5);
        counterclickscroll = 1;
        $('.slide_gallery_right').click(function(){
          counterclickscroll ++;
          if(counterclickscroll > ciclos) { 
            counterclickscroll = ciclos;
            return false;
          }
          $('.view-colaboradores .view-content').animate({scrollLeft:960 * counterclickscroll},2000); 
        })
        $('.slide_gallery_left').click(function(){
          counterclickscroll --;
          if(counterclickscroll < 1){   
            counterclickscroll = 1;
            return false;
          }
          $('.view-colaboradores .view-content').animate({scrollLeft:960 * (counterclickscroll - 1)},1000);         
        })

        var scroll = 0;
          var mouse_in = false;
          var posx_pointer = 0;
          var scroll_speed = 2;    
          var qwidth = $().menu_quicktabs_width();
          var scroll_limit_right = Math.ceil(gallencierra.width()/2 - 100);  
          var scroll_limit_left = Math.ceil(gallencierra.width() - scroll_limit_right);
          gallencierra.mouseover(function(e) {       
            mouse_in = true;
            posx_pointer = e.pageX;     
            //scroll_limit_right = Math.ceil(gallencierra.width() / 3);  
            //scroll_limit_left = Math.ceil(gallencierra.width() - scroll_limit_right);  
          }).mouseout(function(){
            mouse_in = false;
          }); 
            process = setInterval(function(){
            if (mouse_in) {
              gallencierra.each(function() {  
                /* Manejo de scroll */
                //console.log(scroll_limit_right, scroll_limit_left, qwidth, posx_pointer);
                if (posx_pointer > scroll_limit_right && scroll < qwidth) {
                  scroll = scroll + scroll_speed;
                }
                if (posx_pointer <= scroll_limit_left && scroll >= scroll_speed) {
                  scroll = scroll - scroll_speed;
                }

                /* Manejo de flechas */
                if (scroll  > 0) {
                  $('.slide_gallery_left', this).addClass('active');
                } else {
                  $('.slide_gallery_left', this).removeClass('active');
                }

                if (scroll  < qwidth - 15) {
                  $('.slide_gallery_right', this).addClass('active');
                } else {
                  $('.slide_gallery_right', this).removeClass('active');
                }
                
                $('.slide_gallery_content', this).scrollLeft(scroll);     
                $('.view-content', this).scrollLeft(scroll);          
              }); 
            }
          }, 10);
    }
    /*$('.view-salas-de-reunion .views-field-field-nid a').colorbox({
      width: 500,
      height: 500,
    })*/    

    $('#og-wall-form .ob_text').addClass('active');
    $('.ob-profile a').click(function(e){
      $('#block-ob-wall-ob-profile').animate({height:'21em'},500).addClass('active')
      e.preventDefault();
      return false;
    })
    $('.ob-close').click(function(){
      $('#block-ob-wall-ob-profile').animate({height:'0'},500).removeClass('active')
    })
      var output = '<div class="s_event_create">Crear Evento</div>';
      $('#block-afb-1').before(output);
      $('.s_event_create').click(function(){
        if($(this).hasClass('active')){
          $(this).removeClass('active');
          $('#block-afb-1').animate({height: 0},500).removeClass('active');
        } else {
          $(this).addClass('active');
          $('#block-afb-1').addClass('active')
          $('#block-afb-1').animate({height: 730},500, function(){
            $(this).css('height','auto');
          })
        }
      })
      var output = '<div class="s_import_create">Agregar Calendario</div>';
      $('#block-afb-2').before(output);
      $('.s_import_create').click(function(){
        if($(this).hasClass('active')){
          $(this).removeClass('active');
          $('#block-afb-2').animate({height: 0},500).removeClass('active');
        } else {
          $(this).addClass('active');
          $('#block-afb-2').addClass('active')
          $('#block-afb-2').animate({height: 730},500, function(){
            $(this).css('height','auto');
          })
        }
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
      $('.views-exposed-form .views-widget-filter-combine').hide_label();
      $('#og-wall-form').once('wall_form',function(){
        var form = $(this);
        $('label').click(function(){
          $('.active', form).removeClass('active');
          $(this).parents('.s_add_file').addClass('active');
        })
      });
      
      $('.field-name-ds-user-picture a', context).once('init-colorbox-node-processed', function () {
          var url = $(this).attr('href');
          url = url + '?width=600&height=400';
          $(this).attr('href', url);
          $(this).colorboxNode({'launch': false});
      });

      $('#quicktabs-salas_de_reuni_n .quicktabs-tabpage').each(function(){
        var nid = $('.field-name-nid .field-item', this).html();
        $('.field-name-field-nid input').val(nid);
      })

      $('.view-paneador .view-content td.single-day').each(
        function(){
          $ (this).hidde_cal()
        }
      );
    }
  };

  $.fn.hidde_cal = function() {
    clases = new Array();
    $('.view-item-paneador',this).each(function(){
      var clase = $('.views-field-php .s_colortype', this).attr('class');
      clase = clase.replace('s_colortype ','');
      clases.push(clase);
    })
    if(clases.length > 0){
      var output = '<div class="s_ind_content_color">';
      for (index in clases) {
        output += '<div class="s_ind_color ' + clases[index] + '"></div>'
      }
      output += '</div>'
      $(output).appendTo($(this));
    }

    $(this).mouseenter(function(){
      $('.inner',this).stop(true).show().animate({opacity:1},300);

    }).mouseleave(function(){
      $('.inner',this).stop(true).animate({opacity:0},300,function(){
        $(this).hide();
      });
    })
  }  

  $.fn.menu_quicktabs_width = function() {
      width = 0;
      $('.view-colaboradores .views-row').each(function() {
        width = width + $(this).width();
      }); 

      return width;
    }    
})(jQuery);