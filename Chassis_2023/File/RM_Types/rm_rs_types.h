#ifndef RM_RS_TYPES_H
#define RM_RS_TYPES_H
#include "rm_redefine_types.h"

#define	Red_1_Hero		1
#define	Red_2_Engineer	2
#define Red_3_Standard 	3
#define Red_4_Standard  4
#define Red_5_Standard  5
#define Red_6_Aerial    6
#define Red_7_Sentry    7
#define	Red_9_Radar     9
    
#define	Blue_1_Hero     101
#define Blue_2_Engineer 102
#define Blue_3_Standard 103
#define Blue_4_Standard 104
#define Blue_5_Standard 105
#define Blue_6_Aerial   106
#define Blue_7_Sentry   107
#define	Blue_9_Radar    109


#define GameStatusID    			0x0001
#define GameResultID    			0x0002
#define GameRobotHPID   			0x0003
#define DartStatusID    			0x0004
#define ICRABuffDebuffZoneStatusID  0x0005
#define EventDataID     			0x0101
#define SupplyProjectileActionID    0x0102
#define ApplySupplyProjectoleID		0x0103
#define RefereeWaringID     		0x0104
#define DartRemainingTimeID     	0x0105
#define GameRobotStatusID       	0x0201
#define PowerHeatDataID     		0x0202
#define GameRobotPosID      		0x0203
#define BuffID      				0x0204
#define AerialRobotEnergyID     	0x0205
#define RobotHurtID     			0x0206
#define ShootDataID     			0x0207
#define BulletRemainingID   		0x0208
#define RFIDStatusID        		0x0209
#define DartClientCmdID     		0x020A
#define RobotInteractiveDataID  	0x0301

#define ClientCustomGraphicDeleteID		0x0100
#define ClientCustomGraphicSingleID		0x0101
#define ClientCustomGraphicDoubleID		0x0102
#define ClientCustomGraphicFiveID		0x0103
#define ClientCustomGraphicSevenID		0x0104
#define ClientCustomCharacterID			0x0110

#define Custom_Data_Length_MAX			113

/** 模块离线标志结构体 */
typedef struct
{
	bool RSState;			//裁判系统离线
	bool GimbalState;		//下云台云控离线
	bool ComputerState;	//下云台小电脑离线
	bool Can1State;			//CAN1模块离线
	bool Can2State;			//CAN2模块离线
	bool CapacitorState; 	//电容模块异常
} ST_ERROR;
/** 全局标志结构体 */
typedef struct
{
	bool EXTI1_IT_ENABLE_FLAG;
	bool EXTI2_IT_ENABLE_FLAG;


	bool GimbalRunFlag_Pre;	//前次pitch电机运动标记
	bool GimbalRunFlag;			//pitch电机运动标记
	bool ShootFlag;					//拨弹电机运动标记
	bool FrictionFlag;			//摩擦轮启动标志
	bool SniperFlag_Pre;		//前次识别标志
	bool SniperFlag;				//视觉识别物体标记

	bool CS_SPEED_RunFlag;				//底盘速度轮启动标志
	bool CS_SPEED_RunFlag_Pre;		//前次底盘速度轮启动标志
	
	bool CS_SERVO_RunFlag;				//底盘舵向轮启动标志
	bool CS_SERVO_RunFlag_Pre; 		//前次底盘舵向轮启动标志
	
	bool PT_DNFlag;					//空弹仓停电保护标志
	
	bool ResetFlag;					//复位标志位
	bool InitFlag;					//初始化成功标志位
	
} ST_FLAG;

/** 弹夹测试模式结构体 */
typedef struct
{
	bool BoDan_Flag;			//打弹开关
	bool PreBoDan_Flag;			//前次开关状态

	float Fact_PreShootPos;		//前次拨弹位置
	float Fact_ShootPos;		//当前拨弹位置

	s32 Fact_ShootSumNumber;	//测试累积打弹数
	s32 Fact_ShootNumber;		//测试累积打完弹夹数
	s32 Fact_pShootNumber;		//单次统计打弹数
	s32 Des_pShootNumber;		//允许单次上限打弹数

}ST_ShootTestControl;


typedef struct
{
	//实际数据区
	float 	FactSpeed;			//实际底盘运动速度
	float 	FactEnergyBuf;		//实际剩余缓冲能量
	float 	FactPower;			//实际底盘功率
	float	FactCurrent;		//实际底盘输出电流
	float	FactDetectCurrent;	//实际底盘检测电流
	bool 	BufRunOutFlag;		//缓冲能量耗尽标志
	bool 	DangerFlag;			//危机启动标志
	bool 	AccStartFlag;		// 加速开始标志位

	//功率控制
	/** 简易开环控制 */
	float	SetSpeed;			//巡逻目标速度，实际速度由功率环控制
	float	SetCurrentMax;		//功率环输出最大电流 mA
	float	SetPowerMax;		//最大限制功率 W
	
	float	SetPowerLimCoe;		//设置功率补偿系数 mA
	
	float	CapPowerDes;

	/** 闭环控制 */
	bool	AccelFlag;			//加速标志
	float	ControlMode;		//控制环模式
	float	SetLeftSpeed;		//左向稳定巡逻速度	mm/s
	float	SetRightSpeed;		//右向稳定巡逻速度	mm/s
	
	/** 缓冲能量决策 */
	float	DesBufPower;			//目标控制缓冲能量 J

	//撞柱错误自动检测
	bool	StaticDetectFlag;	//静止检测标志
	u32		StaticTick;			//静止时间 ms
	u32		StaticTimeLimit;	//静止时间阈值 ms
	
	/* 变向相关 */
	bool	TurnRoudFlag;					// 变向请求
	bool 	StaticFlag;						// 停止运动请求
	bool	PositionControlFlag;			// 位置控制请求
	
}ST_ChassisMoveControl;

/* 裁判系统数据接收体 */
/** 比赛状态数据：0x0001    发送频率：1Hz
  * @param	game_type	比赛类型：	1-RoboMaster机甲大师赛
  *									2-RoboMaster机甲大师单项赛
  *									3-ICRA RoboMaster人工智能挑战赛
  *									4-RoboMaster联盟赛3V3
  *									5-RoboMaster联盟赛1V1
  *			game_progress	当前比赛阶段：	0-未开始比赛
  *											1-准备阶段
  *											2-自检阶段
  *											3-5s倒计时
  *											4-对战中
  *											5-比赛结算中
  *			stage_remain_time	当前阶段剩余时间，单位s
  *			SyncTimeStamp		机器人接收到该指令的精确Unix时间，当机载端收到有效的NTP服务器授时后生效
  */
typedef __packed struct {
	uint8_t game_type: 4;
	uint8_t game_progress: 4;
	uint16_t stage_remain_time;
	uint64_t SyncTimeStamp;
} ext_game_status_t;



/** 比赛结果数据：0x0002    发送频率：比赛结束后发送
  *	@param	winner	0-平局	1-红方胜利	2-蓝方胜利
  */
typedef __packed struct {
	uint8_t winner;
} ext_game_result_t;



/** 机器人血量数据：0x0003   发送频率：1Hz
* @brief	提供各队机器人血量数据，未上场以及罚下血量为0
  */
typedef __packed struct {
	uint16_t red_1_robot_HP;
	uint16_t red_2_robot_HP;
	uint16_t red_3_robot_HP;
	uint16_t red_4_robot_HP;
	uint16_t red_5_robot_HP;
	uint16_t red_7_robot_HP;
	uint16_t red_outpost_HP;
	uint16_t red_base_HP;
	uint16_t blue_1_robot_HP;
	uint16_t blue_2_robot_HP;
	uint16_t blue_3_robot_HP;
	uint16_t blue_4_robot_HP;
	uint16_t blue_5_robot_HP;
	uint16_t blue_7_robot_HP;
	uint16_t blue_outpost_HP;
	uint16_t blue_base_HP;
} ext_game_robot_HP_t;



/** 人工智能挑战赛加成与惩罚区状态：0x0005   发送频率：1Hz周期发送    发送范围：所有机器人 */
typedef __packed struct {
	uint8_t F1_zone_status: 1;
	uint8_t F1_zone_buff_debuff_status: 3;
	uint8_t F2_zone_status: 1;
	uint8_t F2_zone_buff_debuff_status: 3;
	uint8_t F3_zone_status: 1;
	uint8_t F3_zone_buff_debuff_status: 3;
	uint8_t F4_zone_status: 1;
	uint8_t F4_zone_buff_debuff_status: 3;
	uint8_t F5_zone_status: 1;
	uint8_t F5_zone_buff_debuff_status: 3;
	uint8_t F6_zone_status: 1;
	uint8_t F6_zone_buff_debuff_status: 3;

	uint16_t red1_bullet_left;
	uint16_t red2_bullet_left;
	uint16_t blue1_bullet_left;
	uint16_t blue2_bullet_left;
} ext_ICRA_buff_debuff_zone_status_t;



/** 场地事件数据：0x0101    发送频率：事件改变后发送
  *	@param	bit 0-2：	己方补血点状态
  * 			bit 0：	己方补给站1号补血点占领状态，1为已占领
  *				bit 1：	己方补给站2号补血点占领状态，1为已占领
  *				bit 2：	己方补给站3号补血点占领状态，1为已占领
  *			bit 3-5：	己方能量机关状态
  *				bit 3：	打击点占领状态，1为占领
  *				bit 4：	小能量机关激活状态，1为已激活
  *				bit 5：	大能量机关激活状态，1为已激活
  *			bit 6：		己方R2环形高地占领状态，1为已占领
  *			bit 7：		己方R3梯形高地占领状态，1为已占领
  *			bit 8：		己方R4梯形高地占领状态，1为已占领
  *			bit 9：		己方基地护盾状态
  *				1为基地有虚拟护盾血量
  *				0为基地无虚拟护盾血量
  *			bit 10：	己方前哨站状态
  *				1为前哨站存活
  *				0为前哨站被击毁
  */
typedef __packed struct {
	uint32_t event_type;
} ext_event_data_t;



/** 补给站动作标识：0x0102   发送频率：动作改变后发送    发生范围：己方机器人
  * @param	supply_projectile_id	补给站口ID:	1为1号补给口 2为2号补给口
  *			supply_robot_id			补弹机器人ID: 0为当前无机器人补弹
  *			supply_projectile_step	出弹口开闭状态：0为关闭，1为子弹准备中，2为子弹下落
  *			supply_projectile_num	补弹数量：50/100/150/200
  */
typedef __packed struct {
	uint8_t supply_projectile_id;
	uint8_t supply_robot_id;
	uint8_t supply_projectile_step;
	uint8_t supply_projectile_num;
} ext_supply_projectile_action_t;



/** 裁判警告信息：0x0104    发送频率：警告发生后发送
  *	@param	level	警告等级：1为黄牌，2为红牌，3为判负
  *			foul_robot_id	犯规机器人ID
  *							判负时，机器人ID为0
  *							黄牌、红牌时，机器人ID为犯规机器人ID
  */
typedef __packed struct {
	uint8_t level;
	uint8_t foul_robot_id;
} ext_referee_warning_t;



/** 飞镖发射口倒计时：0x0105  发射频率：1Hz    发送范围：己方机器人 
  *	@param	dart_remaining_time		15s倒计时
  */
typedef __packed struct {
	uint8_t dart_remaining_time;
} ext_dart_remaining_time_t;



/** 比赛机器人状态：0x0201   发送频率：10Hz 
  *	@param	robot_id	本机器人ID
  *			robot_level	机器人等级
  *			remain_HP	机器人剩余血量
  *			max_HP		机器人上限血量
  *			shooter_id1_17mm_cooling_rate	机器人1号17mm枪口每秒冷却值
  *			shooter_id1_17mm_cooling_limit	机器人1号17mm枪口热量上限
  *			shooter_id1_17mm_speed_limit	机器人1号17mm枪口上限速度 单位m/s
  *			shooter_id2_17mm_cooling_rate	机器人2号17mm枪口每秒冷却值
  *			shooter_id2_17mm_cooling_limit	机器人2号17mm枪口热量上限
  *			shooter_id2_17mm_speed_limit	机器人2号17mm枪口上限速度 单位m/s
  *			shooter_id1_42mm_cooling_rate	机器人42mm枪口每秒冷却值
  *			shooter_id1_42mm_cooling_limit	机器人42mm枪口热量上限
  *			shooter_id1_42mm_speed_limit	机器人42mm枪口上限速度 单位m/s
  *			chassis_power_limit			底盘功率限制上限
  *			主控电源输出情况
  *			mains_power_gimbal_output	gimbal口输出	1为有24V输出，0为无24V输出
  *			mains_power_chassis_output	chassis口输出	1为有24V输出，0为无24V输出
  *			mains_power_shooter_output	shooter口输出	1为有24V输出，0为无24V输出
  */
typedef __packed struct {
	uint8_t robot_id;
	uint8_t robot_level;
	uint16_t remain_HP;
	uint16_t max_HP;
	uint16_t shooter_id1_17mm_cooling_rate;
	uint16_t shooter_id1_17mm_cooling_limit;
	uint16_t shooter_id1_17mm_speed_limit;

	uint16_t shooter_id2_17mm_cooling_rate;
	uint16_t shooter_id2_17mm_cooling_limit;
	uint16_t shooter_id2_17mm_speed_limit;

	uint16_t shooter_id1_42mm_cooling_rate;
	uint16_t shooter_id1_42mm_cooling_limit;
	uint16_t shooter_id1_42mm_speed_limit;

	uint16_t chassis_power_limit;
	uint8_t mains_power_gimbal_output: 1;
	uint8_t mains_power_chassis_output: 1;
	uint8_t mains_power_shooter_output: 1;
} ext_game_robot_status_t;



/** 实时功率热量数据：0x0202  发送频率：50Hz 
  * @param	chassis_volt	底盘输出电压 单位mV
  *			chassis_current	底盘输出电流 单位mA
  *			chassis_power	底盘输出功率 单位W
  *			chassis_power_buffer			底盘功率缓冲 单位J	备注：飞坡根据规则增加至250J
  *			shooter_id1_17mm_cooling_heat	1号17mm枪口热量
  *			shooter_id2_17mm_cooling_heat	2号17mm枪口热量
  *			shooter_id1_42mm_cooling_heat	42mm枪口热量
  */
typedef __packed struct {
	uint16_t chassis_volt;
	uint16_t chassis_current;
	float chassis_power;
	uint16_t chassis_power_buffer;
	uint16_t shooter_id1_17mm_cooling_heat;
	uint16_t shooter_id2_17mm_cooling_heat;
	uint16_t shooter_id1_42mm_cooling_heat;
} ext_power_heat_data_t;



/** 机器人位置：0x0203     发送频率：10Hz
  *	@param	x	位置x坐标，单位m
  *			y	位置y坐标，单位m
  *			z	位置z坐标，单位m
  *			yaw	位置枪口，单位°
  */
typedef __packed struct {
	float x;
	float y;
	float z;
	float yaw;
} ext_game_robot_pos_t;



/** 机器人增益：0x0204     发送频率：1Hz
  *	@param	bit 0:	机器人血量补血状态
  *			bit 1:	枪口热量冷却加速
  *			bit 2:	机器人防御加成
  *			bit 3:	机器人攻击加成
  */
typedef __packed struct {
	uint8_t power_rune_buff;
} ext_buff_t;



/** 空中机器人能量状态：0x0205     发送频率：10Hz
  *	@param	attack_time	可攻击时间 单位s	30s递减至0
  */
typedef __packed struct {
	uint8_t attack_time;
} aerial_robot_energy_t;

/** 伤害状态：0x0206          发送频率：伤害发生后发送
  *	@param	armor_id	当血量变化类型为装甲伤害，代表装甲ID，其中数值为0~4号代表机器人的五个装甲片，
  *						其他血量变化类型，该变量数值为0
  *			hurt_type	血量变化类型
  *							0x00 装甲伤害扣血
  *							0x01 模块掉线扣血
  *							0x02 超射速扣血
  *							0x03 超枪口热量扣血
  *							0x04 超底盘功率扣血
  *							0x05 装甲撞击扣血
  */
typedef __packed struct {
	uint8_t armor_id: 4;
	uint8_t hurt_type: 4;
} ext_robot_hurt_t;



/** 实时射击信息：0x0207    发送频率：射击后发送
  *	@param	bullet_type 子弹类型	1为17mm弹丸	2为42mm弹丸
  *			shooter_id	发射机构ID	1为1号17mm发射机构
  *									2为2号17mm发射机构
  *									3为42mm发射机构
  *			bullet_freq		子弹射频 单位Hz
  *			bullet_speed 	子弹射速 单位m/s
  */
typedef __packed  struct {
	uint8_t bullet_type;
	uint8_t shooter_id;
	uint8_t bullet_freq;
	float bullet_speed;
} ext_shoot_data_t;



/** 子弹剩余发射数：0x0208   发送频率：10Hz周期发送   发送范围：所有机器人发送
*	@param	bullet_remaining_num_17mm	17mm子弹剩余发射数目
*			bullet_remaining_num_42mm	42mm子弹剩余发射数目
*			coin_remaining_num			剩余金币数量
  */
typedef __packed struct {
	uint16_t bullet_remaining_num_17mm;
	uint16_t bullet_remaining_num_42mm;
	uint16_t coin_remaining_num;
} ext_bullet_remaining_t;



/** 机器人RFID状态：0x0209     发送频率：1Hz    发送范围：单一机器人
  *	@param	bit 0:	基地增益点RFID状态
  *			bit 1:	高地增益点RFID状态
  *			bit 2:	能量机关激活点RFID状态
  *			bit 3:	飞坡增益点RFID状态
  *			bit 4:	前哨站增益点RFID状态
  *			bit 5:	资源岛增益点RFID状态
  *			bit 6:	补血点增益点RFID状态
  *			bit 7:	工程机器人补血卡RFID状态
* @brief	RFID状态不完全代表对应的增益或处罚状态，例如敌方已占领的高地增益点，不能获取对应的增益效应
  */
typedef __packed struct {
	uint32_t rfid_status;
} ext_rfid_status_t;



/** 飞镖机器人客户端指令数据：0x020A  发送频率：10Hz   发送范围：单一机器人
  *	@param	dart_launch_opening_status	当前飞镖发射口状态	0为关闭	1为正在开启或者关闭中 2为已经开启
  *			dart_attack_target			飞镖的打击目标，默认为前哨站	1为前哨站 2为基地
  *			target_change_time			切换打击目标时的比赛剩余时间，单位s，从未切换默认0
  *			first_dart_speed			检测到的第一枚飞镖速度，单位0.1m/s/LSB，未检测是为0
  *			second_dart_speed			检测到的第二枚飞镖速度，单位0.1m/s/LSB，未检测是为0
  *			third_dart_speed			检测到的第三枚飞镖速度，单位0.1m/s/LSB，未检测是为0
  *			fourth_dart_speed			检测到的第四枚飞镖速度，单位0.1m/s/LSB，未检测是为0
  *			last_dart_launch_time		最近一次的发射飞镖的比赛剩余时间，单位s，初始值为0
  *			operate_launch_cmd_time		最近一次操作手确定发射指令时的比赛剩余时间，单位s，初始值0
  */
typedef __packed struct {
	uint8_t dart_launch_opening_status;
	uint8_t dart_attack_target;
	uint16_t target_change_time;
	uint8_t first_dart_speed;
	uint8_t second_dart_speed;
	uint8_t third_dart_speed;
	uint8_t fourth_dart_speed;
	uint16_t last_dart_launch_time;
	uint16_t operate_launch_cmd_time;
} ext_dart_client_cmd_t;



/** 交互数据接收信息：0x0301 
*	@param	data_cmd_id	数据段的内容ID
*						0x0200~0x02FF		6+n			己方机器人间通信
*						0x0100				6+2			客户端删除图形
*						0x0101				6+15		客户端绘制一个图形
*						0x0102				6+30		客户端绘制二个图形
*						0x0103				6+75		客户端绘制五个图形
*						0x0104				6+105		客户端绘制七个图形
*						0x0110				6+45		客户端绘制字符图形
*			sender_ID	发送者的ID
*			receiver_ID	接收者的ID
  */
typedef __packed struct {
	uint16_t data_cmd_id;
	uint16_t sender_ID;
	uint16_t receiver_ID;
} ext_student_interactive_header_data_t;



/** 交互数据 机器人间通信：0x0301 */
typedef __packed struct {
	uint8_t data[Custom_Data_Length_MAX];
} robot_interactive_data_t;



/** 客户端删除图形 机器人间通信：0x0301 
  *	@param	data_cmd_id		0x0100
  *			operate_type	图形操作	0-空操作 1-删除图层 2-删除所有
  *			layer			图层数		0~9
  */
typedef __packed struct {
	uint8_t operate_type;
	uint8_t layer;
} ext_client_custom_graphic_delete_t;



/** 图形数据 
  *	@param	graphic_name	图形名		在删除，修改等操作中，作为客户端的索引
  *			operate_type	图形操作	0-空操作 	1-增加 		2-修改 		3-删除
  *			graphic_type	图形类型	0-直线 		1-矩形		2-整圆		3-椭圆
  *										4-圆弧		5-浮点数	6-整型数	7-字符
  *			layre			图层数		0~9
  *			color			颜色		0-红蓝主色	1-黄色		2-绿色		3-橙色
  *										4-紫红色	5-粉色		6-青色		7-黑色
  *										8-白色
  *			start_angle		起始角度，单位°，范围[0,360]
  *			end_angle		终止角度，单位°，范围[0,360]
  *			width			线宽
  *			start_x			起点x坐标
  *			start_y			起点y坐标
  *			radius			字体大小或者半径
  *			end_x			终点x坐标
  *			end_y			终点y坐标
  *	@table
  *		graphic_type		start_angle		end_angle		width		start_x		start_y		radius		end_x		end_y
  *		直线				空				空				线条宽度	起点x坐标	起点y坐标	空			终点x坐标	终点y坐标
  *		矩形				空				空				线条宽度	起点x坐标	起点y坐标	空			对顶角x坐标	对顶角y坐标
  *		正圆				空				空				线条宽度	圆心x坐标	圆心y坐标	半径		空			空
  *		椭圆				空				空				线条宽度	圆心x坐标	圆心y坐标	空			x半轴长度	y半轴长度
  *		圆弧				起始角度		终止角度		线条宽度	圆心x坐标	圆心y坐标	空			x半轴长度	y半轴长度
  *		浮点数				字体大小		小数位有效个数	线条宽度	起点x坐标	起点y坐标			32位浮点数，float
  *		整型数				字体大小		空				线条宽度	起点x坐标	起点y坐标			32位整型数，int32_t
  *		字符				字体大小		字符长度		线条宽度	起点x坐标	起点y坐标	空			空			空
  */
typedef __packed struct {
	uint8_t graphic_name[3];
	uint32_t operate_type: 3;
	uint32_t graphic_type: 3;
	uint32_t layre: 4;
	uint32_t color: 4;
	uint32_t start_angle: 9;
	uint32_t end_angle: 9;
	uint32_t width: 10;
	uint32_t start_x: 11;
	uint32_t start_y: 11;
	uint32_t radius: 10;
	uint32_t end_x: 11;
	uint32_t end_y: 11;
} graphic_data_struct_t;



/** 客户端绘制一个图形 */
//#define ClientCustomGraphicSingleID		0x0101
typedef __packed struct {
	graphic_data_struct_t grapic_data_struct;
} ext_client_graphic_single_t;



/** 客户端绘制二个图形 */
//#define ClientCustomGraphicDoubleID		0x0102
typedef __packed struct {
	graphic_data_struct_t grapic_data_struct[2];
} ext_client_custom_graphic_double_t;



/** 客户端绘制五个图形 */
//#define ClientCustomGraphicFiveID			0x0103
typedef __packed struct {
	graphic_data_struct_t grapic_data_struct[5];
} ext_client_custom_graphic_five_t;



/** 客户端绘制七个图形 */
//#define ClientCustomGraphicSevenID		0x0104
typedef __packed struct {
	graphic_data_struct_t grapic_data_struct[7];
} ext_client_custom_graphic_seven_t;



/** 客户端绘制字符 */
//#define ClientCustomCharacterID			0x0110
typedef __packed struct {
	graphic_data_struct_t grapic_data_struct;
	uint8_t data[30];
} ext_client_custom_character_t;


#endif
