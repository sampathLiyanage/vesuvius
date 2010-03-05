
<?php

/** 
 * Home Page of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
?>
<div id="home">
<h2><?php echo  _t('Missing Person Registry'); ?></h2>
<?php
global $global;
if(file_exists($global['approot'].'/www/tmp/mprfound.png')){
?>
<img src="tmp/mprfound.png"/>
<img src="tmp/mprfound.png"/>
<?php
}
?>
<p>
<?php echo  _t('The Missing person registry is an online bulletin board of missing and found people.
It captures information about the people missing and found, as well as information on the person seeking them, increasing the chances
of people finding each other. For example if two members of a family unit are
looking for the head of the family, we can use this data to at least connect those two
family members.'); ?>

</p>

<br></br>
    <div><h3><b><em><?php echo  (_t("Features Include:")) ?></em></b></h3></div>
<br></br>


<ul>
    <li><?php echo  _t('Submitting information about the individual such as identification numbers, physical appearance, last seen location, status, etc'); ?></li>
    <li><?php echo  _t('\'Sounds-like\' name search allowing search even the spelling of the name is not known exactly'); ?></li>
    <li><?php echo  _t('Facilitate uploading of missing person\'s photograph'); ?></li>
    <li><?php echo  _t('Grouping by \'Family Unit\' or other group category'); ?></li>
</ul>

<strong><?php echo _t("Description of Actions:"); ?></strong><br/>
    <ul>
        <li><a href="index.php?mod=mpr&act=search&type=all"><b><?php echo  _t('Search for a person'); ?> </b></a><br/><?php echo  _t('Search to see whether a lost person is registered in the system'); ?></li>
        <li><a href="index.php?mod=mpr&act=addmp&type=missing"><b><?php echo  _t('Report a missing person'); ?> </b> </a><br/><?php echo  _t('Report details about a missing person'); ?></li>
        <li><a href="index.php?mod=mpr&act=search&type=missing"><b><?php echo  _t('Edit missing person'); ?></b></a><br/><?php echo  _t('Update the details of missing person entered to the database previously'); ?></li>
        <li><a href="index.php?mod=mpr&act=addmp&type=found"><b><?php echo  _t('Report a found person'); ?></b></a><br/><?php echo  _t('Report information if the displaced person is found'); ?>
        <li><a href="index.php?mod=mpr&act=list_missing"><b><?php echo  _t('List missing people'); ?></b></a><br/><?php echo  _t('List all information on missing persons available in the database'); ?></li>
        <li><a href="index.php?mod=mpr&act=list_found"><b><?php echo  _t('List found people'); ?></b></a><br/><?php echo  _t('List all the information on people found'); ?></li>
        
</ul>
<br/>


</div>
<?php
/*
 *  Recent Found People people Top 6
 */
global $global,$conf;
require ($global['approot'] . 'mod/mpr/mpr_lib.inc');
?>
<div id="home_recent">
<h1><?php echo  _t('Latest updates on Found People'); ?></h1>
<?php
$limitp = $conf['mod_mpr_pictures_per_page'];

$type = "found";
$det_arr = shn_mpr_get_latest($type,$limitp);
shn_mpr_search_show_verticle($det_arr);

?>
<?php


/*
 *  Recent Missing People Top 6
 */
?>
<h1><?php echo  _t('Latest updates on Missing People'); ?></h1>
<?php
//$limit = $conf['mod_mpr_pictures_per_page'];

$type = "missing";
$det_arr = shn_mpr_get_latest($type,$limitp);
shn_mpr_search_show_verticle($det_arr);
?>
</div>
<?php
/**
 * Shows the latest updates on missing and found perople
 * 
 * @param string $type 
 * @param int $limit 
 * @access public
 * @return void
 */
 
function shn_mpr_get_latest($type,$limit=6)
{
	global $global;
    $incident_join = "INNER JOIN resource_to_incident e ON a.p_uuid = e.x_uuid ";
    $sql_missing = "
            SELECT
                a.p_uuid AS p_uuid, a.full_name AS full_name, 
                b.height AS height, b.weight AS weight, 
                b.opt_eye_color AS opt_eye_color, 
                b.opt_skin_color AS opt_skin_color, b.opt_hair_color AS opt_hair_color, 
                c.last_seen AS last_seen, c.last_clothing AS last_clothing, 
                c.comments AS comments 
            FROM person_uuid a 
            LEFT OUTER JOIN person_physical b USING (p_uuid) 
            INNER JOIN person_missing c USING (p_uuid)
            INNER JOIN person_status d USING (p_uuid) 
            $incident_join 
            WHERE d.opt_status = 'mis' AND e.incident_id = '{$_SESSION['user_pref_ims_incident_id']}' 
            ORDER BY d.updated DESC";

    $sql_found = "
            SELECT
                a.p_uuid AS p_uuid, a.full_name AS full_name, 
                b.height AS height, b.weight AS weight, 
                b.opt_eye_color AS opt_eye_color, 
                b.opt_skin_color AS opt_skin_color, b.opt_hair_color AS opt_hair_color, 
                c.last_seen AS last_seen, c.last_clothing AS last_clothing, 
                c.comments AS comments 
            FROM person_uuid a 
            LEFT OUTER JOIN person_physical b USING (p_uuid) 
            INNER JOIN person_missing c USING (p_uuid)
            INNER JOIN person_status d USING (p_uuid) 
            $incident_join
            WHERE d.opt_status != 'mis' AND e.incident_id = '{$_SESSION['user_pref_ims_incident_id']}'
            ORDER BY d.updated DESC";

	$final_sql="";
    if($type=='missing')
    {
        $final_sql=$sql_missing;
        $rs = $global['db']->SelectLimit($sql_missing,$limit,$offset);
        
    }
    elseif($type=='found')
     {
     	$final_sql=$sql_found;     
        $rs = $global['db']->SelectLimit($sql_found,$limit,$offset);
     }
     $rs = $global['db']->SelectLimit($final_sql,$limit);
     if($rs)
     $arr = $rs->GetAll();
     
     return $arr;
}
 

?>
