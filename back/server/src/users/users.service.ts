import { HttpException, HttpStatus, Inject, Injectable } from '@nestjs/common';
import { Stat } from 'src/stats/entities/stat.entity';
import { Repository } from 'typeorm';
import { CreateUserDto } from './dto/create-user.dto';
import { ResUserMyPage } from './dto/res-user-mypage.dto';
import { UpdateUserDto } from './dto/update-user.dto';
import { User } from './entities/user.entity';

@Injectable()
export class UsersService {
	constructor(
		@Inject('USER_REPOSITORY')
		private userRepository: Repository<User>,
	) { }


	async findOneMyPage(intraId : string)
	{
		const userRepo = await this.userRepository.findOne({
			relations: ["stats"],
			where: {
				intra_id: intraId,
			}
		});
		if (userRepo == undefined)
			throw new HttpException(`${intraId}: Cannot find user`, HttpStatus.BAD_REQUEST);
		return (new ResUserMyPage(userRepo));
	}

	create(createUserDto: CreateUserDto, file: Express.Multer.File) {
		return this.saveUser(createUserDto, file);
	}

	async update(intraId: string, updateUserDto: UpdateUserDto, file: Express.Multer.File) {
		if (await this.userRepository.findOneBy({ intra_id: intraId }) == undefined)
			throw new HttpException(`${intraId}: Cannot find user`, HttpStatus.BAD_REQUEST)
		
		const ipv4 = await this.getIpAdrress();
		if (updateUserDto.nickName !== undefined) {

			if (await this.isNickAvailable(updateUserDto.nickName)) {
				console.log('nickname updated');
				console.log(updateUserDto);
				this.userRepository.update(intraId, {
					nickname: updateUserDto.nickName,
				});
			}
		}
		if (file !== undefined) {
			console.log("avatar updated");
			this.userRepository.update(intraId, {
				avatar: `http://${ipv4}:3000/public/avatar/${file.filename}`,
			});
		}
		return `update`;
	}

	private async saveUser(createUserDto: CreateUserDto, file: Express.Multer.File)
	{
		const user = new User();
		const filePath = `avatar/${file.filename}`;
		const ipv4 = await this.getIpAdrress();

		user.intra_id = createUserDto.intraId;
		user.nickname = createUserDto.nickName;
		user.intra_email = createUserDto.intraEmail;
		user.avatar = `http://${ipv4}:3000/public/${filePath}`;
		user.status = createUserDto.status;
		user.role = createUserDto.role;
		user.channel_id = createUserDto.channelId;
		user.stats = new Stat();

		return await this.userRepository.save(user);
	}

	private async isNickAvailable(nickName: string) {
		const users = await this.userRepository.find({
			where: {
				nickname: nickName
			}
		})
		if (users.length === 0)
		{
			return (true);
		}
		else
		{
			throw new HttpException(`${nickName}: Nickname already exist`, HttpStatus.FORBIDDEN);
		}
	}

	private async getIpAdrress()
	{
		const { networkInterfaces } = require('os');
		const nets = networkInterfaces();
		const ipv4 = nets['en0'][1]['address'];
		return (ipv4);
	}

}
