// DO NOT EDIT. This file is machine-generated and constantly overwritten.
// Make changes to KBBeer.m instead.

#import "_KBBeer.h"

@implementation KBBeerID
@end

@implementation _KBBeer

+ (id)insertInManagedObjectContext:(NSManagedObjectContext*)moc_ {
	NSParameterAssert(moc_);
	return [NSEntityDescription insertNewObjectForEntityForName:@"KBBeer" inManagedObjectContext:moc_];
}

+ (NSString*)entityName {
	return @"KBBeer";
}

+ (NSEntityDescription*)entityInManagedObjectContext:(NSManagedObjectContext*)moc_ {
	NSParameterAssert(moc_);
	return [NSEntityDescription entityForName:@"KBBeer" inManagedObjectContext:moc_];
}

- (KBBeerID*)objectID {
	return (KBBeerID*)[super objectID];
}




@dynamic type;






@dynamic id;






@dynamic name;






@dynamic info;






@dynamic rating;



- (float)ratingValue {
	NSNumber *result = [self rating];
	return result ? [result floatValue] : 0;
}

- (void)setRatingValue:(float)value_ {
	[self setRating:[NSNumber numberWithFloat:value_]];
}






@dynamic abv;



- (float)abvValue {
	NSNumber *result = [self abv];
	return result ? [result floatValue] : 0;
}

- (void)setAbvValue:(float)value_ {
	[self setAbv:[NSNumber numberWithFloat:value_]];
}






@dynamic country;






@dynamic imageName;






@dynamic ratings;

	
- (NSMutableSet*)ratingsSet {
	[self willAccessValueForKey:@"ratings"];
	NSMutableSet *result = [self mutableSetValueForKey:@"ratings"];
	[self didAccessValueForKey:@"ratings"];
	return result;
}
	

@dynamic kegs;

	
- (NSMutableSet*)kegsSet {
	[self willAccessValueForKey:@"kegs"];
	NSMutableSet *result = [self mutableSetValueForKey:@"kegs"];
	[self didAccessValueForKey:@"kegs"];
	return result;
}
	



@end
