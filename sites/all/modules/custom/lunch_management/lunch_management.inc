<?php
/**
* @file
* function for module
*/

/*

function report1(){

$sql = db_select('tbl_lunch','t');
$sql->fields('t',array('foodid','uid','fitem','fdescript','price','fimage'));
$results = $sql->execute(); 

/*
$sql1 = db_select('tbl_food','t');
$sql1->fields('t',array('fid','fitem','fdescript','price','fimage'))
$sql1->fields('f',array('uri'));
$results = $sql1->execute();


echo '<table>';
echo '<tr>';
echo '<th>No.</th><th>Name</th><th>Descp.</th><th>price</th><th>Picture</th>';
echo '</tr>';
foreach($results as $result){
echo '<tr>';
echo '<td>'. $result->foodid .'</td>';
echo '<td>'. $result->fitem .'</td>';
echo '<td>'. $result->fdescript .'</td>';
echo '<td>'. $result->price .'</td>';
//echo '<td>' . $result->fimage . '</td>';


$fid = $result->fimage;
echo '<td>' .$fid .'</td>';
//$file = file_load($fid);
/**$image = image_load($file->uri);
  $content = array(
  'file' => array(
    '#theme' => 'image_style',
    '#style_name' => 'small',
    '#path' => $image->source,
    '#width' => $image->info['width'],
    '#height' => $image->info['height'],
  ),
 
);
*/

//echo '<td>' . drupal_render($content) . '</td>';
//$output .= "<p><img src=\"".$file['filepath']."\" alt=\"\" /></p>";

//echo '<td>'. '<img src = \'' . $file->uri . '\' alt=\'\' />';
//finding image's uri

/**
$q1 = db_select('file_managed','f')
     ->condition('f.fid',$ffid,'=')
     ->fields('f',array('uri'));
$uri1 = $q1->execute()->fetchField();
//echo '<td>'. $result->fimage .'</td>';
//echo '<td>' . '<img src =\''. $uri1 .'\'>' . '</td>';
echo '<td>' . '<img src =\"' . $uri1 . '\" >' .'</td>';
drupal_set_message(t($uri1));



echo '</tr>';
}

echo'</table>';
//drupal_set_message(t($));
}

*/

/**
* function for report
*/


/**
   //get item's picture
    $file = file_load($fid);
    $image = image_load($file->uri);
    $content = array(
  'file' => array(
    '#theme' => 'image_style',
    '#style_name' => 'small',
    '#path' => $image->source,
    '#width' => $image->info['width'],
    '#height' => $image->info['height'],
  ),
 
);
echo drupal_render($content);
*/

function freport(){
 global $user;

 //using theme_pager to fetch result
// This is only for test, study how to output the report

 $header = array(
             array('data' => t('No.'), 'field' => 'foodid', 'sort' => 'asc'), // sort
             array('data' => t('Item'), 'field' => 'fitem'),
             array('data' => t('Description'), 'field' => 'fdescript'),
             array('data' => t('Price'), 'field' => 'price'),
             array('data' => t('Picture'), 'field' => 'fimage'),
             array('data'=>t('Option'),''),
           ); //test

  //select item, it belongs to supplier
    $query = db_select('tbl_lunch', 't');
   
    $query->fields('t', array('foodid','uid', 'fitem', 'fdescript','price','fimage'));
    $query->condition('uid',$user->uid);
   
   //$sql = "SELECT t.foodid, count(t.foodid) as total_c, t.uid, t.fitem,t.fdescript,t.price,t.fimage FROM {tbl_lunch} t WHERE t.uid = $user->uid";
   //$query = db_query($sql);
    //$query->condition('uid',$user->uid);
    $table_sort = $query->extend('TableSort') // Add table sort extender.
                        ->orderByHeader($header); // Add order by headers.
    $pager = $table_sort->extend('PagerDefault')
                        ->limit(5); // 5 rows per page.
    $result = $pager->execute();
    $rows = array();
    
   
   // $total_c = $result->rowCount();
 // listing
   
    $i = 1; 
   foreach($result as $res){
    
      //$fid = $res->fimage;
     // $fid = 13;
     // $file = file_load($fid);

      //$image = image_load($file->uri);
    ///$content = array(
     //'file' => array(
     //'#theme' => 'image_style',
     //'#style_name' => 'small',
    // '#path' => $image->source,
     //'#width' => $image->info['width'],
     //'#height' => $image->info['height'],
  //),
 
//); 
 
     /*<input name="checkbox[]" type="checkbox" id="checkbox[]" value="<? echo $rows['id']; ?>">*/

      //$rows[] = array($res->foodid, $res->fitem, $res->fdescript, $res->price,drupal_render($content),'<input type=checkbox value=\'$res->foodid\' name = \'checkbox[]\' id = \'checkbox[]\' />');

$rows[] = array($i, $res->fitem, $res->fdescript, $res->price, $res->fimage,"<a href='?q=app/" .$res->foodid. "/delete'>" . t('Delete') . "</a> | <a href='?q=app/" . $res->foodid. "/edit'>". t('Edit') . "</a>");
    $i++;
    }


//echo drupal_render($content);

/**
 $query = db_select('tbl_lunch','t')
   ->join('ftype','f','t.typeid=f.typeid');
 $query->fields('t', array('fid', 'fitem', 'fdescript','price','fimage'));
   ->condition('f.uid',$user->uid);
 $table_sort = $query->extend('TableSort') // Add table sort extender.
                        ->orderByHeader($header); // Add order by headers.
    $pager = $table_sort->extend('PagerDefault')
                        ->limit(5); // 5 rows per page.
    $result = $pager->execute();
    $rows = array();


 // listing
    foreach($result as $res){
      $rows[] = array($res->fid, $res->fitem, $res->fdescript, $res->price,$res->fimage);

    }
*/
  //<input name="delete" type="submit" id="delete" value="Delete">
   //show result in table using theme_pager
   $output ='';
   $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'sort-table'))); 
   $output .= theme('pager');
  
// $output.='<br><input type = button value = Edit />&nbsp
//<input name = delete type = submit id = delete value = Delete>';
   return $output;
   //drupal_set_message(t($file->uri));
}


//this function is placed on features which havent ever create
function notice(){
return t('This page is underconstruction. Please visit later.');
}


/**
* order form
*/

//its merely test
function myorder_form($form, &$form_state) {
  //order date
/*
  $form['o_date'] = array(
    '#type' => 'date_popup',
    '#title' => 'Date',
    '#description' => t('Select a day'),
    '#default_value' => date('c'), //check that out: date in ISO format
     '#date_format' => 'd-m-Y',
     '#date_label_position' => 'within',
     '#date_timezone' => 'Europe/Rome',
     '#date_increment' => 15,
     '#date_year_range' => '0:+2',
     '#required' => TRUE,
 );*/

 $form['o_date'] = array(
 '#type'=>'date',
 '#title'=>'order date',);

 $form['otype'] = array(
  '#title'=>t('Type'),
  '#type'=>'select',
  '#options'=>_load_type(),
  '#ajax'=> array(
    'event'=>'change',
    'callback'=>'myorder_form_food',
    'wrapper'=>'food-wrapper',    
) );

//select supplier


  $form['supl'] = array(
  '#title'=>t('Supplier\'s name'),
  '#type'=>'select',
  '#options'=>_load_sup(),
  '#ajax'=> array(
    'event'=>'change',
    'callback'=>'myorder_form_food',
    'wrapper'=>'food-wrapper',    
) );


/*
 $opt= array('- Select a type -');
  if (isset($form_state['values']['supl'])) {
    $opt = _load_type($form_state['values']['supl']);
  }
  // food type dropdown list
  $form['otype'] = array(
    '#title' => t('Type of food'),
    '#type' => 'select',
    '#options' => $opt,
    '#ajax' => array(
      'event'=>'change',
      'callback' =>'myorder_form_food',
      'wrapper' => 'food-wrapper',
    ),
  );
*/

  // Wrapper for food's item dropdown list
  $form['wrapper'] = array(
    '#prefix' => '<div id="food-wrapper">',
    '#suffix' => '</div>',
  );

  // Options for food dropdown list
 /*
  if(isset($form_state['values']['supl'])){
  	$ssup = $form_state['values']['supl'];
  }else{
  	
  }
  $ssup = $form_state['values']['supl'];
 */
  
  
 $options = array('- Select an item -');

 //stuff
 /*
 $gettype = chk_val($form_state['values']['otype']);
 
 if(isset($form_state['values']['supl'])){
 	$ssup = $form_state['values']['supl'];
 	$options = _load_food($gettype, $ssup);
 }else{
 	
 }

 
 
 if(isset($form_state['values']['otype'])){
 	$gettype = $form_state['values']['otype'];
 	if(isset($form_state['values']['supl'])){
 		$ssup = $form_state['values']['supl'];
 		$option = _load_food($gettype, $ssup);
 	}else{// ! isset $ssup, else 2
 		
 	 $query = db_select('tbl_lunch', 't');
     $query ->fields('t', array('typeid', 'foodid', 'fitem'));
     $query->condition('t.typeid', $typeid, '=');
    // $query->condition('t.uid',$sup, '=');
     $query->orderBy('t.fitem');
     $result = $query->execute();

  while($row = $result->fetchObject()){
    // Key-value pair for dropdown options
    $options[$row->foodid] = $row->fitem;
  }// end while
 }//end else 2
}else{ // !isset(otype)
	//$option = _load_food(0, $form_state['values']['supl']);
	$gettype = 0;
	if(isset($form_state['values']['supl'])){
		$ssup = $form_state['values']['supl'];
		$option = _load_food($gettype, $ssup);
	}else{
		//!isset($ssup)
		$query = db_select('tbl_lunch', 't');
		$query ->fields('t', array('foodid', 'fitem'));
		//$query->condition('t.typeid', $typeid, '=');
		// $query->condition('t.uid',$sup, '=');
		$query->orderBy('t.fitem');
		$result = $query->execute();
		while($row = $result->fetchObject()){
			$option[$row->foodid] = $row->fitem;
		}
	}
}
*/
 if(isset($form_state['values']['otype'])){
 	$options = _load_food($form_state['values']['otype']);
 }
 //print_r($options);
  // type dropdown list
 // $form['wrapper']['food'] = array(
   $form['wrapper']['food'] = array(
    '#title' => t('Food'),
    '#type' => 'select',
    '#multiple'=>TRUE,
    '#options' => $options,
  );
  //$curItem = $form_state['values']['food'];
  //$f_choice = callback_4_btnadd($curItem);
 // $lst array();

// $f_choice = array();

 //foreach($options as $key=>$value){
// 	array_push($f_choice,$value);
// }
  
  $f_choice = array(1=>t('item1'),2=>t('item2'),3=>t('item3'));
  
  //$f_choice = array();
  
  $form['lstfood'] = array(
  	'#title'=>t('list of choices'),
  	'#theme'=>'item_list',
  	//'#items'=>callback_4_btnadd($form_state['values']['food']),
    '#items'=>$f_choice,
    //'#default_value'=>$fchoice,
  );
  // Form submit button
  $form['submit'] = array(
    '#value'  => t('Submit'),
    '#type'   => 'submit',
    //"#submit" => array("myorder_form_submit"),
  );
  //$curItem = $form_state['values']['food'];
 
  

  $form['actions']['add'] = array(
  		'#type' => 'submit',
  		//'#attributes' => array('onClick' => 'location.replace("'. referer_uri() .'"); return false;'),
  		'#value' => t('Add'),
  		//'#name'=>'add',
  		'#submit' => array('callback_4_btnadd'),
  		'#limit_validation_errors' => array(),
  );
  /*
  $form['add_list']['btnadd'] = array(
  	'#value'=>t('Add'),
  	'#type'=>'button',
  	//'#name'=>'add_more',
  	//'#submit'=>array('callback_4_btnadd',$curItem),
  	'#ajax'=>array(
  	  //'event'=>'change',
  	   'method'=>'replace',
  	   'action'=>'click',
  	   'callback'=>'callback_4_btnadd', 
  	   'wrapper'=>'add_list',
  	   'executes_submit_callback'=>FALSE,
  ),
  );*/
  
  return $form;
}

//callback for btnadd button


function callback_4_btnadd($form,&$form_state){
//$lst = array();
$i = $form['otype']['#options'][$form_state['values']['otype']];
return drupal_set_message($i);
}

//
/**
 * Function for handling ajax request
 */
function myorder_form_food($form, $form_state) {
  // Return the dropdown list including the wrapper
  return $form['wrapper'];
}

/**
* loading supplier
*/


function _load_sup(){
$sup = array('-select a supplier-');
$query = db_select('users','u');
$query->fields('u',array('uid','name'));
$query->join('users_roles','r','u.uid=r.uid');
$query->condition('r.rid',4); //select user where rid = 4 -> supplier
$result = $query->execute();
while($row = $result->fetchObject()){
$sup[$row->uid] = $row->name;
}
return $sup;
}

/**
 * Function for populating type
 */

function _load_type() {

  $otype = array('-select type-');

  // Select table
  $query = db_select("ftype", "f");
  // Selected fields
  $query->fields("f", array('typeid', 'tname'));
 
  // Order by name
  $query->orderBy("f.tname");
  // Execute query

 $result = $query->execute();

  while($row = $result->fetchObject()){
    // Key-value pair for dropdown options
    $otype[$row->typeid] = $row->tname;
  }

/*
 $query = db_select("ftype","f");
 $query->fields("f",array('uid','typeid','tname'));
 $query->condition('uid',$sup_id,'=');
 $query->orderBy("f.tname");
 $result = $query->execute();
 while($row = $result->fetchObject()){
 $otype[$row->typeid] = $row->tname;
 } */
  return $otype;
}

/**
 * Function for populating food
 */
function _load_food($typeid) {
  $food = array('- Select items -');
 /*
  // Select table
  $query = db_select('tbl_lunch', 't');
  // Selected fields
  $query->fields('t', array('typeid','foodid', 'fitem'));
  
  $query->condition('t.typeid', $typeid,'=');
  // Order by name
  $query->orderBy('t.fitem');
  // Execute query
  $result = $query->execute();*/
 
  $query = db_select('tbl_lunch', 't');
  $query ->fields('t', array('typeid', 'foodid', 'fitem'));
  $query->condition('t.typeid', $typeid, '=');
  //$query->condition('t.uid',$sup, '=');
  $query->orderBy('t.fitem');
  $result = $query->execute();

  while($row = $result->fetchObject()){
    // Key-value pair for dropdown options
    $food[$row->foodid] = $row->fitem;
  }

  return $food;
}

/*stuff
 * 
 */
/*
function chk_val($val){
	if(isset($val)){
		//$ref = $val;
		return $val;
	}else{
		//$ref = 0;
	}
	//return $ref;
	return 0;
} */
function myorder_form_submit($form, &$form_state){
    global $user;
    
     $item = $form_state['values']['supl'];
    /*
    $query = db_select('tbl_lunch', 't');
    $query->condition('t.foodid', $item, '=');
    
    $query->fields('t',array('foodid'));
    $result = $query->execute()->fetchField();
	$orderId = db_insert('orders')
	->fields(array(
			'uid'=>$user->uid,
			'orderdate'=>$form_state['values']['o_date'],
	))
	->execute();
	db_insert('orderDetails')
	->fields(array(
		'orderId'=>$orderId,
		'foodid'=>$result,
	))
	->execute();
  
*/
    
//drupal_set_message(t($item));

}
?>