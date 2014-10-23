<?php
/**
* @file
* edit, delete function
*/

//confirm delete task

function delete_item_record_comfirm_form($form, &$form_state, $foodid){
  
  $form['delete'] = array(
    '#type' => 'value',
    '#value' => $foodid,
  );
  return confirm_form(
    $form,
    t('Are you sure you want to delete this?'),
    'app/',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

//delete an item
function delete_item_record_comfirm_form_submit($form, &$form_state) { 
  $record = $form_state['values']['delete'];
 
 
  if ($record ) {
     // delete fid from file_managed table
     $img2del = db_query('SELECT fimage FROM {tbl_lunch} t WHERE t.foodid = :record', array(':record'=>$record))->fetchField();
     db_delete('file_managed')
    ->condition('fid',$img2del,'=')
    ->execute();
    //delete food item
    $num_deleted = db_delete('tbl_lunch')
      ->condition('foodid', $record,'=' )
      ->execute();
    drupal_set_message('The record has been deleted!');
  }
  $form_state['redirect'] = "app/";
}

function form_values_edit($id){
  $id_val = $id;
  /**
  $mydef = db_select('tbl_lunch', 't')
    //->fields('t')
    ->join('ftype','f')
    ->condition('t.typeid','f.typeid','=')
    ->condition('foodid', $id_val,'=' )
    ->fields('t')
    ->fields('f')
    ->execute()
    ->fetchAssoc();
    
    */
  //_load_img(10);
 // _fetch_data();

  $query = db_select('tbl_lunch', 't');
 // $query->join('ftype', 'f', 'f.typeid = t.typeid');
  $mydef = $query
  ->condition('foodid', $id_val, '=')
  ->fields('t', array('foodid','fitem','fdescript','fimage','price'))
 // ->fields('f', array('typeid','tname'))
  ->execute()
  ->fetchAssoc();
  return drupal_get_form('app_form', $mydef); 


/*test image 

$rs = db_query("SELECT f.fid, f.uri FROM {file_managed} f WHERE f.uid = 2");
 $fid = $rs->execute();
 $upload_record = file_load($fid);
  $url = $upload_record->uri;

  $render_image = theme(
    'image_style', 
    array(
      'style_name' => 'Style_name', 
      'path' => $url, 
      'getsize' => TRUE, 
      'attributes' => array(
        'width' => '250', 
        'height' => '162')
      )
    );
 print $render_image;
*/

}

//fetch item's image from database
function _load_img($fid){
if(!isset($fid)||($fid == 0)) {
 $f_img = t('No Picture');
}else{
$file = file_load($fid);
$image = image_load($file->uri);
$content = array(
  'file' => array(
    '#theme' => 'image_style',
    '#style_name' => 'large',
    '#path' => $image->source,
    '#width' => $image->info['width'],
    '#height' => $image->info['height'],
  ),
);
$f_img = drupal_render($content);
}
//echo drupal_render($content);
return $f_img;
}

//fetch data info and return to html table

function _fetch_data(){
 $results = db_select('tbl_lunch', 't')
         ->fields('t', array('foodid', 'fitem', 'fdescript','price','fimage'))
         ->execute();
/*
 $query = db_select('tbl_lunch', 't');
 $query->join('file_managed', 'f', 'f.uid=t.uid');
 $results = $query
    ->fields('t', array('foodid', 'fitem', 'fdescript','price','fimage'))
    ->fields('f', array('fid'))
    ->execute();*/

 //drupal_add_css(drupal_get_path('modules','lunch_management'). '/css.css');
 
 $output ='';
 //$output = '<div class = "\shopp\">';
 $output .= '<table>';
 $output .= '<tr>';
 $output .= '<th>Name</th><th>Descp.</th><th>price</th><th>picture</th>';
 $output .= '</tr>';

 foreach($results as $rs){
  $ffid = $rs->fimage;
  $output .= '<tr>';
  $output .= '<td>'. $rs->fitem . '</td>';
  $output .= '<td>' .$rs->fdescript .'</td>';
  $output .= '<td>' . $rs->price .'</td>';
  $output .= '<td>' . _load_img($ffid) .'</td>';
  $output .= '</tr>';
//$output.= '<div class =\"label\">';
//$output.= $rs->fitem;
//$output.=$rs->fdescript;
//$output.='</div>';
 /* print 'Name :'.$rs->fitem .'<br>';
  print 'Description :'.$rs->fdescript .'<br>';
  print 'Price :'.$rs->price .'<br>';
  print 'Picture :'._load_img($fid) .'<br>';*/
 }
 $output .= '</table>';
 //$output.= '</div>';
 print $output;
}
