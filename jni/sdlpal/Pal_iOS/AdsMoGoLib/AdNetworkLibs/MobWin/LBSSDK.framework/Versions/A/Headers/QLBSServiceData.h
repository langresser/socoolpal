//
//  QLBSServiceData.h
//  qqlbsSDK
//
//  Created by ease lin on 7/13/11.
//  Copyright 2011 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

/** @brief GPS类型 */
typedef enum
{
	kGPS_WGS84 = 0,		/**<  WGS-84系统的坐标(一般手机硬件读到数值的是该系统) */
	kGPS_MARS = 1,		/**< 火星坐标(按保密局要求加扰后的坐标，用于国内地图展示或POI相对位置处理等) */
	kGPS_WGS_REAL = 2,	/**< 确认输入为硬件读出来的GPS，而不是像iphone或android自己使用cell、wifi定位的数值 */
} QLBSGPSType;

/** @brief GPS信息 */
@interface QLBSGPSInfo : NSObject
/**
 *	@brief GPS类型 
 *	@note 如果是从手机硬件读出来的，要设置为WGS84
 */
@property(nonatomic,assign) QLBSGPSType type;
/** @brief 纬度 */
@property(nonatomic,assign) double lat;
/** @brief 经度 */
@property(nonatomic,assign) double log;
/** @brief 海拨 */
@property(nonatomic,assign) double alt;
@end

/** @brief 当前的地理位置信息 */
@interface QLBSPosition : NSObject
/** 
 *	@brief 用户的坐标，火星坐标 
 *	@note 可用于在google地图与soso地图上准确显示
 */
@property (nonatomic, retain) QLBSGPSInfo* marsGps;
/** 
 *	@brief 定位的精确度
 *	@note -1表示无此信息 
 */
@property (nonatomic, assign) NSInteger range;
/** @brief 省、直辖市、自治区、特别行政区 */
@property (nonatomic, retain) NSString* province;
/** @brief 地区、地级市、自治州、盟 */
@property (nonatomic, retain) NSString* city;
/** @brief 县级市、自治县、旗、自治旗、特区、林区，以及市辖区 */
@property (nonatomic, retain) NSString* district;
/** @brief 乡、镇、民族乡、街道 */
@property (nonatomic, retain) NSString* town;
/** @brief 路、街道 */
@property (nonatomic, retain) NSString* road;
/**
 *	@brief 周边地标
 *	@note 不推荐直接使用，大多为空，如"腾讯大厦;XX茶餐厅"，以;分隔，建议仅在描述当前点时使用
 */
@property (nonatomic, retain) NSString* premises;
/** 
 *	@brief 行政区号(像身份证号前6位) 
 */
@property (nonatomic, assign) NSInteger districtCode;
/** 
 *	@brief 从高到低拼合地点信息
 *	@return 描述该地点的字符串指针
 */
- (NSString*)locationString;
@end

/** 
 *	@brief POI类型，这里是一级分类，便于程序使用，二级、三级分类由于条数太多，需要的请向roycelin索取详细文件，接口输入的“接受分类”属性可以输入任意级别的分类
 */
enum {
	kPOI_FOOD     = 100000, /**< 美食 */
	kPOI_COM      = 110000, /**< 公司企业 */
	kPOI_ORG      = 120000, /**< 机构团体 */
	kPOI_SHOPPING = 130000, /**< 购物 */
	kPOI_SERVICE  = 140000, /**< 生活服务 */
	kPOI_ENTM     = 160000, /**< 休闲娱乐 */
	kPOI_BEAUTY   = 170000, /**< 美容美发 */
	kPOI_SPORT    = 180000, /**< 运动健身 */
	kPOI_CAR      = 190000, /**< 汽车 */
	kPOI_HEALTH   = 200000, /**< 医疗保健 */
	kPOI_HOTEL    = 210000, /**< 酒店宾馆 */
	kPOI_TOUR     = 220000, /**< 旅游景点 */
	kPOI_CULTURE  = 230000, /**< 文化场馆 */
	kPOI_SCHOOL   = 240000, /**< 教育学校 */
	kPOI_BANK     = 250000, /**< 银行金融 */
	kPOI_PLACE    = 260000, /**< 地名地址 */
	kPOI_INFRA    = 270000, /**< 基础设施 */
	kPOI_ESTATE   = 280000, /**< 房产小区 */
};

/** @brief POI热点信息 */
@interface QLBSPoiInfo : NSObject
/** @brief poi名称 */
@property (nonatomic, retain) NSString* name;
/** @brief 类型id */
@property (nonatomic, assign) int type;
/** @brief 类型名称 */
@property (nonatomic, retain) NSString* typeName;
/** @brief poi地址 */
@property (nonatomic, retain) NSString* address;
/** @brief poiID */
@property (nonatomic, assign) uint64_t poiID;
/** @brief 行政区划编码(与身份证号前6位意义相同) */
@property (nonatomic, assign) int districtCode;
/** @brief 火星坐标点 */
@property (nonatomic, retain) QLBSGPSInfo* marsGps;
/** @brief 离输入点距离(单位:米) */
@property (nonatomic, assign) int distance;
/** @brief 热度值 */
@property (nonatomic, assign) int hotValue;
@end

/** @brief POI列表集合 */
@interface QLBSPoiInfoBatch : NSObject
/** @brief 返回的POI列表信息(元素为 @ref QLBSPoiInfo) */
@property (nonatomic, retain) NSMutableArray* poiList;
/** @brief 可获取的全部POI数量 */
@property (nonatomic, assign) int totalNum;
/** @brief 用户位置 采用火星坐标 */
@property (nonatomic, retain) QLBSGPSInfo* marsGps;
@end

