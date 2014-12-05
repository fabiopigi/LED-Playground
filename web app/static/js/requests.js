$(document).ready(function() {


    $('#loopbutton').click(function() {
        token = $("#token").val();
        url = sprintf("/api/loopOff/token/%s", token);
        $.get(url);

    });


    //KnightRider
    var kr_delay = $("#kr_delay").slider({
        min: 1, max: 50, value: 5, step:1,
        formatter: function(value) {
            return 'Delay: ' + value + 'ms';
        }
    });
    var kr_width = $("#kr_width").slider({
        min: 1, max: 15, value: 4, step:1,
        formatter: function(value) {
            return 'Width: ' + value + 'px';
        }
    });
    var kr_cycles = $("#kr_cycles").slider({
        min: 1, max: 10, value: 2, step:1,
        formatter: function(value) {
            return 'Cycles: ' + value;
        }
    });
    var kr_color = $('#kr_color').colorselector();

    $('#kr_button').click(function() {
        delay = $("#kr_delay").val();
        cycles = $("#kr_cycles").val();
        width = $("#kr_width").val();
        color = $("#kr_color").val();
        token = $("#token").val();
        loop = $("#looptoggle").is(':checked')?"loop/":"";

        $("button").prop('disabled', true);
        //http://rgb.cmdesign.com/api/knightRider/color/FF00FF/delay/3/width/4/cycles/3/token/piggy
        url = sprintf("/api/knightRider/color/%s/delay/%i/width/%i/cycles/%s/token/%s/%s", color,delay,width,cycles,token,loop);
        $.get( url).always(function() {
            $("button").prop('disabled', false);
        });
        ;
    });







    //ColorWipe
    var cw_delay = $("#cw_delay").slider({
        min: 1, max: 50, value: 10, step:1,
        formatter: function(value) {
            return 'Delay: ' + value + 'ms';
        }
    });

    var cw_cycles = $("#cw_cycles").slider({
        min: 1, max: 10, value: 1, step:1,
        formatter: function(value) {
            return 'Cycles: ' + value;
        }
    });
    var cw_color = $('#cw_color').colorselector();

    $('#cw_button').click(function() {
        delay = $("#cw_delay").val();
        cycles = $("#cw_cycles").val();
        color = $("#cw_color").val();
        token = $("#token").val();
        loop = $("#looptoggle").is(':checked')?"loop/":"";

        $("button").prop('disabled', true);
        url = sprintf("/api/colorWipe/color/%s/delay/%i/cycles/%s/token/%s/%s", color,delay,cycles,token,loop);
        $.get( url).always(function() {
            $("button").prop('disabled', false);
        });
        ;
    });





    //RainbowFade
    var rf_delay = $("#rf_delay").slider({
        min: 1, max: 50, value: 10, step:1,
        formatter: function(value) {
            return 'Delay: ' + value + 'ms';
        }
    });

    var rf_cycles = $("#rf_cycles").slider({
        min: 1, max: 10, value: 1, step:1,
        formatter: function(value) {
            return 'Cycles: ' + value;
        }
    });

    var rf_brightness = $("#rf_brightness").slider({
        min: 1, max: 100, value: 100, step:1,
        formatter: function(value) {
            return 'Brightness: ' + value + '%';
        }
    });

    $('#rf_button').click(function() {
        delay = $("#rf_delay").val();
        cycles = $("#rf_cycles").val();
        brightness = $("#rf_brightness").val();
        token = $("#token").val();
        loop = $("#looptoggle").is(':checked')?"loop/":"";

        $("button").prop('disabled', true);
        url = sprintf("/api/rainbowFade/delay/%i/cycles/%i/brightness/%i/token/%s/%s",delay,cycles,brightness,token,loop);
        $.get( url).always(function() {
            $("button").prop('disabled', false);
        });
        ;
    });




    //RainbowPattern
    var rp_delay = $("#rp_delay").slider({
        min: 0, max: 50, value: 10, step:1,
        formatter: function(value) {
            return 'Delay: ' + value + 'ms';
        }
    });

    var rp_cycles = $("#rp_cycles").slider({
        min: 1, max: 10, value: 1, step:1,
        formatter: function(value) {
            return 'Cycles: ' + value;
        }
    });
    var rp_density = $("#rp_density").slider({
        min: 1, max: 5, value: 1, step:1,
        formatter: function(value) {
            return 'Density: ' + value + ' Rainbows';
        }
    });

    var rp_brightness = $("#rp_brightness").slider({
        min: 1, max: 100, value: 100, step:1,
        formatter: function(value) {
            return 'Brightness: ' + value + '%';
        }
    });

    $('#rp_button').click(function() {
        delay = $("#rp_delay").val();
        cycles = $("#rp_cycles").val();
        density = $("#rp_density").val();
        brightness = $("#rp_brightness").val();
        token = $("#token").val();
        loop = $("#looptoggle").is(':checked')?"loop/":"";

        $("button").prop('disabled', true);
        url = sprintf("/api/rainbowPattern/delay/%i/density/%i/cycles/%i/brightness/%s/token/%s/%s",delay,density,cycles,brightness,token,loop);
        $.get( url).always(function() {
            $("button").prop('disabled', false);
        });
        ;
    });






    //SparkleColor
    var sc_delay = $("#sc_delay").slider({
        min: 1, max: 50, value: 5, step:1,
        formatter: function(value) {
            return 'Delay: ' + value + 'ms';
        }
    });
    var sc_density = $("#sc_density").slider({
        min: 1, max: 99, value: 30, step:1,
        formatter: function(value) {
            return 'Density: ' + value + ' Promille';
        }
    });
    var sc_cycles = $("#sc_cycles").slider({
        min: 1, max: 50, value: 5, step:1,
        formatter: function(value) {
            return 'Cycles: ' + value;
        }
    });
    var sc_color = $('#sc_color').colorselector();

    $('#sc_button').click(function() {
        delay = $("#sc_delay").val();
        cycles = $("#sc_cycles").val();
        density = $("#sc_density").val();
        color = $("#sc_color").val();
        rainbow = $("#sc_rainbow").is(':checked');
        token = $("#token").val();
        loop = $("#looptoggle").is(':checked')?"loop/":"";

        if(rainbow){
            url = sprintf("/api/sparkleRainbow/delay/%i/density/%i/cycles/%s/token/%s/%s",delay,density,cycles,token,loop);
        }else{
            url = sprintf("/api/sparkleColor/color/%s/delay/%i/density/%i/cycles/%s/token/%s/%s", color,delay,density,cycles,token,loop);
        }

        $("button").prop('disabled', true);
        $.get( url).always(function() {
            $("button").prop('disabled', false);
        });
        ;
    });




});