<?php
require 'vendor/autoload.php';
//http://www.slimframework.com




$app = new \Slim\Slim();
$app->config('debug', true);
//$app->response->header('Content-Type', 'text/plain');

header('Content-Type: application/json;charset=utf-8');

\Slim\Route::setDefaultConditions(array(
    'color' => '([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})',
    'delay' => '[0-9]{1,3}',
    'width' => '[0-9]{1,2}',
    'cycles' => '[0-9]{1,2}',
    'brightness' => '[0-9]{1,3}',
    'density' => '[0-9]{1,2}',
    'token' => 'all|your|tokens|for|apps|or|friends'
));




//Loop Off
$app->get('/loopOff/token/:token(/)', function ($token) {
    $app = \Slim\Slim::getInstance();
    $params = "LO,0";
    $url = 'route/';
    $data = array('params'=>$params);
    sendPost($url,$data);
    exit;
});


//KnightRider
$app->get('/knightRider/color/:color/delay/:delay/width/:width/cycles/:cycles/token/:token(/(:loop(/)))', function ($color,$delay,$width,$cycles,$token,$loop=0) {
    $app = \Slim\Slim::getInstance();
    if($loop === "loop"){
        $lp = "LO,1,";
        $cycles = 1;
    }else{
        $lp = "";
    }
    $params = sprintf("%sKR,%03d,%02d,%02d,%s",$lp,$delay,$width,$cycles,$color);
    //speed,width,cycles,color
    $url = 'route/';
    $data = array('params'=>$params);
    sendPost($url,$data);
    exit;
});



//ColorWipe
$app->get('/colorWipe/color/:color/delay/:delay/cycles/:cycles/token/:token(/(:loop(/)))', function ($color,$delay,$cycles,$token,$loop=0) {
    $app = \Slim\Slim::getInstance();
    if($loop === "loop"){
        $lp = "LO,B,";
        $cycles = 1;
    }else{
        $lp = "";
    }
    $params = sprintf("%sCW,%03d,%02d,%s",$lp,$delay,$cycles,$color);
    //speed,cycles,color
    $url = 'route/';
    $data = array('params'=>$params);
    sendPost($url,$data);
    echo $params;
    exit;
});




//RainbowFade
$app->get('/rainbowFade/delay/:delay/cycles/:cycles/brightness/:brightness/token/:token(/(:loop(/)))', function ($delay,$cycles,$brightness,$token,$loop=0) {
    $app = \Slim\Slim::getInstance();
    if($loop === "loop"){
        $lp = "LO,1,";
        $cycles = 1;
    }else{
        $lp = "";
    }
    $params = sprintf("%sRF,%03d,%02d,%03d",$lp,$delay,$cycles,$brightness);
    //speed,cycles,color
    $url = 'route/';
    $data = array('params'=>$params);
    sendPost($url,$data);
    echo $params;
    exit;
});




//RainbowPattern
$app->get('/rainbowPattern/delay/:delay/density/:density/cycles/:cycles/brightness/:brightness/token/:token(/(:loop(/)))', function ($delay,$density,$cycles,$brightness,$token,$loop=0) {
    $app = \Slim\Slim::getInstance();
    if($loop === "loop"){
        $lp = "LO,1,";
        $cycles = 1;
    }else{
        $lp = "";
    }
    $params = sprintf("%sRP,%03d,%02d,%01d,%03d",$lp,$delay,$cycles,$density,$brightness);
    //speed,cycles,color
    $url = 'route/';
    $data = array('params'=>$params);
    sendPost($url,$data);
    echo $params;
    exit;
});


//SparkleColor
$app->get('/sparkleColor/color/:color/delay/:delay/density/:density/cycles/:cycles/token/:token(/(:loop(/)))', function ($color,$delay,$density,$cycles,$token,$loop=0) {
    $app = \Slim\Slim::getInstance();
    if($loop === "loop"){
        $lp = "LO,1,";
        $cycles = 1;
    }else{
        $lp = "";
    }
    $params = sprintf("%sSC,%03d,%02d,%02d,%s",$lp,$delay,$density,$cycles,$color);
    //speed,width,cycles,color
    $url = 'route/';
    $data = array('params'=>$params);
    sendPost($url,$data);
    exit;
});


//SparkleRainbow
$app->get('/sparkleRainbow/delay/:delay/density/:density/cycles/:cycles/token/:token(/(:loop(/)))', function ($delay,$density,$cycles,$token,$loop=0) {
    $app = \Slim\Slim::getInstance();
    if($loop === "loop"){
        $lp = "LO,1,";
        $cycles = 1;
    }else{
        $lp = "";
    }
    $params = sprintf("%sSR,%03d,%02d,%02d",$lp,$delay,$density,$cycles);
    //speed,width,cycles,color
    $url = 'route/';
    $data = array('params'=>$params);
    sendPost($url,$data);
    exit;
});




function sendPost($url,$data){

    //Configuration
    $data['access_token'] = "YOUR_ACCESS_TOKEN_HERE";
    $url = "https://api.spark.io/v1/devices/YOUR_DEVICE_ID_HERE/".$url;

    $options = array(
        'http' => array(
            'header'  => "Content-type: application/x-www-form-urlencoded\r\n",
            'method'  => 'POST',
            'content' => http_build_query($data),
        ),);
    $context  = stream_context_create($options);
    $result = file_get_contents($url, false, $context);
    var_dump($result);
}


$app->run();


?>